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
    {
        std::cout << "  Price: " << bid.GetPrice() 
                  << ", Quantity: " << bid.GetQuantity() << std::endl;
    }
    
    std::cout << "\nAsks (Sell Orders):" << std::endl;
    for (const auto& ask : orderInfos.GetAsks())
    {
        std::cout << "  Price: " << ask.GetPrice() 
                  << ", Quantity: " << ask.GetQuantity() << std::endl;
    }
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
    std::cout << "=== Orderbook Testing with Dummy Orders ===\n" << std::endl;
    
    Orderbook orderbook;
    
    // Test 1: Add some buy orders (bids)
    std::cout << "Test 1: Adding Buy Orders (Bids)" << std::endl;
    std::cout << "Adding buy orders at different price levels..." << std::endl;
    
    auto buyOrder1 = std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Buy, 100, 50);
    auto buyOrder2 = std::make_shared<Order>(OrderType::GoodTillCancel, 2, Side::Buy, 99, 30);
    auto buyOrder3 = std::make_shared<Order>(OrderType::GoodTillCancel, 3, Side::Buy, 101, 20);
    
    auto trades1 = orderbook.AddOrder(buyOrder1);
    auto trades2 = orderbook.AddOrder(buyOrder2);
    auto trades3 = orderbook.AddOrder(buyOrder3);
    
    PrintTrades(trades1);
    PrintTrades(trades2);
    PrintTrades(trades3);
    PrintOrderbookState(orderbook);
    
    // Test 2: Add some sell orders (asks) - should match with bids
    std::cout << "Test 2: Adding Sell Orders (Asks) - Should Match with Bids" << std::endl;
    std::cout << "Adding sell orders that should match with existing bids..." << std::endl;
    
    auto sellOrder1 = std::make_shared<Order>(OrderType::GoodTillCancel, 4, Side::Sell, 99, 25);
    auto sellOrder2 = std::make_shared<Order>(OrderType::GoodTillCancel, 5, Side::Sell, 100, 40);
    
    auto trades4 = orderbook.AddOrder(sellOrder1);
    auto trades5 = orderbook.AddOrder(sellOrder2);
    
    PrintTrades(trades4);
    PrintTrades(trades5);
    PrintOrderbookState(orderbook);
    
    // Test 3: Test Fill and Kill order
    std::cout << "Test 3: Fill and Kill Order" << std::endl;
    std::cout << "Adding a fill-and-kill order that should be cancelled if not matched..." << std::endl;
    
    auto fillAndKillOrder = std::make_shared<Order>(OrderType::FillAndKill, 6, Side::Sell, 95, 10);
    auto trades6 = orderbook.AddOrder(fillAndKillOrder);
    
    PrintTrades(trades6);
    PrintOrderbookState(orderbook);
    
    // Test 4: Test Fill or Kill order
    std::cout << "Test 4: Fill or Kill Order" << std::endl;
    std::cout << "Adding a fill-or-kill order that should be cancelled if not fully filled..." << std::endl;
    
    auto fillOrKillOrder = std::make_shared<Order>(OrderType::FillOrKill, 7, Side::Buy, 102, 100);
    auto trades7 = orderbook.AddOrder(fillOrKillOrder);
    
    PrintTrades(trades7);
    PrintOrderbookState(orderbook);
    
    // Test 5: Test Market order
    std::cout << "Test 5: Market Order" << std::endl;
    std::cout << "Adding a market order that should match at best available price..." << std::endl;
    
    auto marketOrder = std::make_shared<Order>(OrderType::Market, 8, Side::Buy, 0, 15);
    auto trades8 = orderbook.AddOrder(marketOrder);
    
    PrintTrades(trades8);
    PrintOrderbookState(orderbook);
    
    // Test 6: Cancel an order
    std::cout << "Test 6: Cancel Order" << std::endl;
    std::cout << "Cancelling order ID 3..." << std::endl;
    
    orderbook.CancelOrder(3);
    PrintOrderbookState(orderbook);
    
    // Test 7: Modify an order
    std::cout << "Test 7: Modify Order" << std::endl;
    std::cout << "Modifying order ID 2 to change price and quantity..." << std::endl;
    
    OrderModify modifyOrder(2, Side::Buy, 98, 25);
    auto trades9 = orderbook.ModifyOrder(modifyOrder);
    
    PrintTrades(trades9);
    PrintOrderbookState(orderbook);
    
    // Test 8: Add more orders to test depth
    std::cout << "Test 8: Adding More Orders to Test Orderbook Depth" << std::endl;
    
    auto buyOrder4 = std::make_shared<Order>(OrderType::GoodTillCancel, 9, Side::Buy, 97, 35);
    auto buyOrder5 = std::make_shared<Order>(OrderType::GoodTillCancel, 10, Side::Buy, 96, 45);
    auto sellOrder3 = std::make_shared<Order>(OrderType::GoodTillCancel, 11, Side::Sell, 103, 60);
    auto sellOrder4 = std::make_shared<Order>(OrderType::GoodTillCancel, 12, Side::Sell, 104, 40);
    
    auto trades10 = orderbook.AddOrder(buyOrder4);
    auto trades11 = orderbook.AddOrder(buyOrder5);
    auto trades12 = orderbook.AddOrder(sellOrder3);
    auto trades13 = orderbook.AddOrder(sellOrder4);
    
    PrintTrades(trades10);
    PrintTrades(trades11);
    PrintTrades(trades12);
    PrintTrades(trades13);
    PrintOrderbookState(orderbook);
    
    // Test 9: Test Good For Day order
    std::cout << "Test 9: Good For Day Order" << std::endl;
    std::cout << "Adding a good-for-day order..." << std::endl;
    
    auto goodForDayOrder = std::make_shared<Order>(OrderType::GoodForDay, 13, Side::Sell, 105, 30);
    auto trades14 = orderbook.AddOrder(goodForDayOrder);
    
    PrintTrades(trades14);
    PrintOrderbookState(orderbook);
    
    std::cout << "=== Testing Complete ===" << std::endl;
    std::cout << "Final orderbook state:" << std::endl;
    PrintOrderbookState(orderbook);
    
    return 0;
}
/*
#include "Orderbook.h"

int main()
{
    Orderbook orderbook;
    // Do work.
    
    return 0;
}
*/