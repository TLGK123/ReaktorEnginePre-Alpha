using System;
using System.Runtime.InteropServices;
using System.Text;

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
        //   DoSomething3("这段数据来自c#");
           
           DoSomething4((f)=>Console.WriteLine("C# Print c++ data :"+ f));
           
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
       
        
    }
}