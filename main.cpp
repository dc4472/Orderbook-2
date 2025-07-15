#include "Orderbook.h"
#include <iostream>
#include <iomanip>

void PrintOrderbookState(const Orderbook& orderbook)
{
    std::cout << "\n=== Orderbook State ===" << std::endl;
    std::cout << "Total Orders: " << orderbook.Size() << std::endl;
    auto orderInfos = orderbook.GetOrderInfos();
    std::cout << "\nBids (Buy Orders):" << std::endl;
    for (const auto& bid : orderInfos.GetBids())
        std::cout << "  Price: " << bid.price_ << ", Quantity: " << bid.quantity_ << std::endl;
    std::cout << "\nAsks (Sell Orders):" << std::endl;
    for (const auto& ask : orderInfos.GetAsks())
        std::cout << "  Price: " << ask.price_ << ", Quantity: " << ask.quantity_ << std::endl;
    std::cout << "====================\n" << std::endl;
}

void PrintTrades(const Trades& trades)
{
    if (trades.empty())
    {
        std::cout << "No trades executed." << std::endl;
        return;
    }
    std::cout << "\n=== Executed Trades ===" << std::endl;
    for (size_t i = 0; i < trades.size(); ++i)
    {
        const auto& trade = trades[i];
        std::cout << "Trade " << (i + 1) << ":" << std::endl;
        std::cout << "  Bid Order ID: " << trade.GetBidTrade().orderId_ 
                  << " @ Price: " << trade.GetBidTrade().price_ 
                  << " Quantity: " << trade.GetBidTrade().quantity_ << std::endl;
        std::cout << "  Ask Order ID: " << trade.GetAskTrade().orderId_ 
                  << " @ Price: " << trade.GetAskTrade().price_ 
                  << " Quantity: " << trade.GetAskTrade().quantity_ << std::endl;
    }
    std::cout << "====================\n" << std::endl;
}

int main()
{
    std::cout << "=== Orderbook Edge Case & Functionality Testing ===\n" << std::endl;
    Orderbook orderbook;

    // 1. Add an ask at $95 for 600 shares
    std::cout << "Adding ASK: $95 x 600 (OrderId 1001)" << std::endl;
    auto ask95_600 = std::make_shared<Order>(OrderType::GoodTillCancel, 1001, Side::Sell, 95, 600);
    orderbook.AddOrder(ask95_600);
    PrintOrderbookState(orderbook);

    // 2. Add a bid at $95 for 350 shares (should partially match)
    //std::cout << "Adding BID: $95 x 350 (OrderId 2001) -- should partially match" << std::endl;
    auto bid95_350 = std::make_shared<Order>(OrderType::GoodTillCancel, 2001, Side::Buy, 95, 350);
    auto trades1 = orderbook.AddOrder(bid95_350);
    //PrintTrades(trades1);
    //PrintOrderbookState(orderbook);
    /*

    // 3. Add another bid at $95 for 300 shares (should fill the rest and leave 50 unfilled on the bid)
    std::cout << "Adding BID: $95 x 300 (OrderId 2002) -- should fill remaining ask and leave 50 on bid" << std::endl;
    auto bid95_300 = std::make_shared<Order>(OrderType::GoodTillCancel, 2002, Side::Buy, 95, 300);
    auto trades2 = orderbook.AddOrder(bid95_300);
    PrintTrades(trades2);
    PrintOrderbookState(orderbook);

    // 4. Cancel the remaining bid (OrderId 2002)
    std::cout << "Cancelling BID OrderId 2002 (should remove remaining 50 shares at $95 bid)" << std::endl;
    orderbook.CancelOrder(2002);
    PrintOrderbookState(orderbook);

    // 5. Add and then modify an order
    std::cout << "Adding BID: $94 x 100 (OrderId 2003)" << std::endl;
    auto bid94_100 = std::make_shared<Order>(OrderType::GoodTillCancel, 2003, Side::Buy, 94, 100);
    orderbook.AddOrder(bid94_100);
    PrintOrderbookState(orderbook);

    std::cout << "Modifying BID OrderId 2003 to $96 x 120 (should move to new price level)" << std::endl;
    OrderModify mod2003(2003, Side::Buy, 96, 120);
    auto trades3 = orderbook.ModifyOrder(mod2003);
    PrintTrades(trades3);
    PrintOrderbookState(orderbook);

    // 6. Show active order count
    std::cout << "Active order count (Size): " << orderbook.Size() << std::endl;

    // 7. Add a FillOrKill order that cannot be fully filled
    std::cout << "Adding FOK BID: $95 x 1000 (OrderId 2004) -- should not be added (not enough ask)" << std::endl;
    auto fokBid = std::make_shared<Order>(OrderType::FillOrKill, 2004, Side::Buy, 95, 1000);
    auto trades4 = orderbook.AddOrder(fokBid);
    PrintTrades(trades4);
    PrintOrderbookState(orderbook);

    // 8. Add a FillAndKill order that can be partially filled
    std::cout << "Adding FAK ASK: $96 x 120 (OrderId 1002) -- should match with $96 bid" << std::endl;
    auto fakAsk = std::make_shared<Order>(OrderType::FillAndKill, 1002, Side::Sell, 96, 120);
    auto trades5 = orderbook.AddOrder(fakAsk);
    PrintTrades(trades5);
    PrintOrderbookState(orderbook);

    std::cout << "=== Testing Complete ===" << std::endl;
*/
    return 0;
}