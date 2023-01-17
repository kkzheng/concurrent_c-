#include <thread>
#include <iostream>
#include <string>
#include <chrono>
#include <future>

void work(std::string name) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "i am " << name << std::endl;
}

int work_res(std::string name, int val) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  return val + 1;
}

void work_promise(std::string name, std::promise<int>& prom) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  prom.set_value(27);
}

int main() {
  std::thread th1(work, "jinhao zhang");
  th1.join();

  // async
  auto fut_async = std::async(work_res, "zhangjinhao", 27);
  std::cout << "main thread while async" << std::endl;
  std::cout << "value of fut_async: " << fut_async.get() << std::endl;

  // promise
  std::promise<int> prom;
  std::future<int> fut_prom = prom.get_future();
  std::thread th2(work_promise, "jinhao", std::ref(prom));
  std::cout << "main thread while promise" << std::endl;
  std::cout << "value of fut_promise: " << fut_prom.get() << std::endl;
  th2.join();

  // packages_task
  std::packaged_task<int(std::string, int)> task(work_res);
  std::future<int> fut_pack = task.get_future();
  std::thread th3(std::move(task), "hao", 27);
  std::cout << "main thread while packaged_task" << std::endl;
  std::cout << "value of packaged_task: " << fut_pack.get() << std:: endl;
  th3.join();

  return 0;
}
