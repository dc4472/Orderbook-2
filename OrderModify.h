#pragma once

#include "Order.h"

class OrderModify
{
public:
    OrderModify(OrderId orderId, Side side, Price price, Quantity quantity, bool isMaker = false)
        : orderId_{ orderId }
        , price_{ price }
        , side_{ side }
        , quantity_{ quantity }
        , isMaker_{ isMaker }
    { }

    OrderId GetOrderId() const { return orderId_; }
    Price GetPrice() const { return price_; }
    Side GetSide() const { return side_; }
    Quantity GetQuantity() const { return quantity_; }
    bool GetIsMaker() const { return isMaker_; }

    OrderPointer ToOrderPointer(OrderType type) const
    {
        return std::make_shared<Order>(type, GetOrderId(), GetSide(), GetPrice(), GetQuantity(), GetIsMaker());
    }

private:
    OrderId orderId_;
    Price price_;
    Side side_;
    Quantity quantity_;
    bool isMaker_;
};

