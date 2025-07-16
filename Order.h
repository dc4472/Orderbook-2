#pragma once

#include <list>
#include <exception>
#include <format>

#include "OrderType.h"
#include "Side.h"
#include "Usings.h"
#include "Constants.h"


class Order
{
public:
    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity, bool isMaker = false,
          std::uint64_t userId = 0, std::uint64_t marketId = 0, std::uint64_t competitorsId = 0,
          double totalValue = 0.0, double transactionFee = 0.0, Quantity matchedQuantity = 0,
          std::uint64_t expiration = 0, bool isSystemGenerated = false, OrderPointer originalOrder = nullptr,
          std::string transactionHash = "")
        : orderType_{ orderType }
        , orderId_{ orderId }
        , side_{ side }
        , price_{ price }
        , initialQuantity_{ quantity }
        , remainingQuantity_{ quantity }
        , isMaker_{ isMaker }
        , userId_{ userId }
        , marketId_{ marketId }
        , competitorsId_{ competitorsId }
        , totalValue_{ totalValue }
        , transactionFee_{ transactionFee }
        , matchedQuantity_{ matchedQuantity }
        , expiration_{ expiration }
        , isSystemGenerated_{ isSystemGenerated }
        , originalOrder_{ originalOrder }
        , transactionHash_{ transactionHash }
    { }

    Order(OrderId orderId, Side side, Quantity quantity, bool isMaker = false)
        : Order(OrderType::Market, orderId, side, Constants::InvalidPrice, quantity, isMaker)
    { }

    OrderId GetOrderId() const { return orderId_; }
    Side GetSide() const { return side_; }
    Price GetPrice() const { return price_; }
    OrderType GetOrderType() const { return orderType_; }
    Quantity GetInitialQuantity() const { return initialQuantity_; }
    Quantity GetRemainingQuantity() const { return remainingQuantity_; }
    Quantity GetFilledQuantity() const { return GetInitialQuantity() - GetRemainingQuantity(); }
    bool IsFilled() const { return GetRemainingQuantity() == 0; }
    void Fill(Quantity quantity)
    {
        if (quantity > GetRemainingQuantity())
            throw std::logic_error(std::format("Order ({}) cannot be filled for more than its remaining quantity.", GetOrderId()));

        remainingQuantity_ -= quantity;
        matchedQuantity_ += quantity;
    }
    void ToGoodTillCancel(Price price) 
    { 
        if (GetOrderType() != OrderType::Market)
            throw std::logic_error(std::format("Order ({}) cannot have its price adjusted, only market orders can.", GetOrderId()));

        price_ = price;
        orderType_ = OrderType::GoodTillCancel;
    }
    bool GetIsMaker() const { return isMaker_; }
    std::uint64_t GetUserId() const { return userId_; }
    std::uint64_t GetMarketId() const { return marketId_; }
    std::uint64_t GetCompetitorsId() const { return competitorsId_; }
    double GetTotalValue() const { return totalValue_; }
    double GetTransactionFee() const { return transactionFee_; }
    Quantity GetMatchedQuantity() const { return matchedQuantity_; }
    std::uint64_t GetExpiration() const { return expiration_; }
    bool GetIsSystemGenerated() const { return isSystemGenerated_; }
    OrderPointer GetOriginalOrder() const { return originalOrder_; }
    const std::string& GetTransactionHash() const { return transactionHash_; }

private:
    OrderType orderType_;
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity initialQuantity_;
    Quantity remainingQuantity_;
    bool isMaker_;
    std::uint64_t userId_;
    std::uint64_t marketId_;
    std::uint64_t competitorsId_;
    double totalValue_;
    double transactionFee_;
    Quantity matchedQuantity_;
    std::uint64_t expiration_;
    bool isSystemGenerated_;
    OrderPointer originalOrder_;
    std::string transactionHash_;
};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;

