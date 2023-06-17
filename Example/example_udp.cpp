#include <iostream>
#include <chrono>
#include <thread>

#include "../Comm/comm_udp.hpp"

CommUdp comm_udp_;

struct RecvData
{
    /* data */
    int num;
    RecvData()
    {
        num = 0;
    }
};

struct SendData
{   
    int num;
    SendData()
    {
        num = 0;
    }
};

void task_recv()
{
    std::cout << "Recv thread" << std::endl;

    RecvData recv_data;

    while (1)
    {
        comm_udp_.recv_data(reinterpret_cast<uint8_t*>(&recv_data), sizeof(RecvData));

        // Process
        std::cout << recv_data.num << std::endl;

        std::this_thread::sleep_for(std::chrono::microseconds(100000));	
    }
}

void task_send()
{
    std::cout << "Send thread" << std::endl;

    SendData send_data;

    while (1)
    {
        // Process
        send_data.num++;

        comm_udp_.send_data(reinterpret_cast<uint8_t*>(&send_data), sizeof(SendData));
        std::this_thread::sleep_for(std::chrono::microseconds(10000));	
    }
}

int main()
{
    std::cout << "Hello" << std::endl;

    std::thread th_recv(task_recv);
    std::thread th_send(task_send);

    th_recv.join();
    th_send.join();

    return 0;
}