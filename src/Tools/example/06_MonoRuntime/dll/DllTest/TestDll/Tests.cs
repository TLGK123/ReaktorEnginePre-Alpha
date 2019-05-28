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
        }


        [DllImport ("__Internal", EntryPoint="DoSomething")]
        static extern void DoSomething();
        
        [DllImport ("__Internal", EntryPoint="DoSomething2")]
        static extern void DoSomething2(string message);
    }
}