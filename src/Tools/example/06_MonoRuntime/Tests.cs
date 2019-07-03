using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace TestDll
{
    public  class Main
    {
        
        public static void SayHello()
        {
           string s = "おはよう";
           Console.WriteLine(s);
           DoSomething();
           DoSomething2("我也很无奈啊");

            //var c= DoSomething3("这段数据来自c#");
            //Console.WriteLine(c);
            int ws = 90;
            ws += 7;
            DoSomething4((f)=>Console.WriteLine("C# Print c++ data :"+ f));
           

           
           Console.WriteLine("Main treard start ---");
           
           Main m = new Main();
           
           
           Thread t = new Thread(m.PrintNanme);
           t.Start(" wang wu");

           for (int i = 0; i < 10; i++)
           {
                Console.WriteLine("main Tread num :  " + i);
                Thread.Sleep(100);
           }
           Console.WriteLine("Main thread: Call Join(), to wait until ThreadProc ends.");
           t.Join();
           Console.WriteLine("Main thread: ThreadProc.Join has returned. ");

        }

        public delegate void  CallFromNative(string cshapdata);

        [DllImport ("__Internal", EntryPoint="DoSomething")]
        static extern void DoSomething();
        
        [DllImport ("__Internal", EntryPoint="DoSomething2")]

        static extern void DoSomething2(string message);  
        
        [DllImport ("__Internal", EntryPoint="DoSomething3")]
        static extern string DoSomething3(string message);
        
        [DllImport ("__Internal", EntryPoint="DoSomething4")]
        static extern void DoSomething4(CallFromNative d);
       
        

        public static void PrintNum()
        {
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine("subTread num :  " + i);
                Thread.Sleep(100);
            }
            
        }
        
        public static void PrintNumInTimes(object times )
        {
            for (int i = 0; i < (int)times; i++)
            {
                Console.WriteLine( "total : "+ times +  " subTread num :  " + i);
                Thread.Sleep(100);
            }
            
        }
        
        public void PrintNanme(object names )
        {
            for (int i = 0; i < (int)5; i++)
            {
                Console.WriteLine( " subTread name :  " + names);
                Thread.Sleep(100);
            }
            
        }


    }
}