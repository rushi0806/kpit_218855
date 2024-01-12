#include<future>
#include<iostream>

/*
    
    option 1: one after the other. Always complete one 
              thing before starting the next task

           Name: SINGLE THREAD technique
    -----------------------------------------------------------------

    option 2: I will complete all tasks in such a way that I
              "practically start all of them at the same time" but keep 
               juggling them based on some criteria

           Name: MULTI-THREAD approach
------------------------------------------------------------------------
    option 3: Map number of task amongst number of available "workers"

           Name: PARALLEL execution
-------------------------------------------------------------------------
    option 4: Start a task. Either delegate it to another worker or do it
              yourself after some time.

              If someone else is doing a task, monitor it, wait for their
              work to be done, take follow-up actions accordingly
              
           Name: ASYNCHRONOUS execution
----------------------------------------------------------------------------
*/

/*
    2 Tasks 
    calculate factorial of 5
    calculate square of a number given by the user
*/

int square( std::future<int>& ft){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"\nHello from square. I have started my work! \n";
    int number =ft.get();
    return number*number;
}

int factorial(int number){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if(number<0){
        throw std::runtime_error("negative number error!");
    }
    else if(number==0 || number==1){
        return 1;
    }
    else{
        return number*factorial(number-1);
    }

}

int main(){
    //step 1: make a promise
    std::promise<int> pr;
    //step 2: A future linked to the promise
    std::future<int> ft = pr.get_future();
    /*
        OS: Launch square(if possible as a new thread)
    */
    std::future<int> result_ft = std::async(std::launch::async,&square,std::ref(ft));
    
    std::cout<<factorial(5);
    int val = 0;
    std::cin>>val;
    pr.set_value(val);

    std::cout<<"\nResult of factorial is: "<<result_ft.get();

    return 0;
}

//to compile code command: g++ async_demo1.cpp -lpthread -o app && ./app
