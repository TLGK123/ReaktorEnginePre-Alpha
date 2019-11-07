using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace TestDll
{
    public class Main
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
            DoSomething4((f) => Console.WriteLine("C# Print c++ data :" + f));
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

            MySystemTime sysTime = new MySystemTime();
            NativeMethods.GetSystemTime(sysTime);

            string dt;
            dt = "System time is: \n" +
                  "Year: " + sysTime.wYear + "\n" +
                  "Month: " + sysTime.wMonth + "\n" +
                  "DayOfWeek: " + sysTime.wDayOfWeek + "\n" +
                  "Day: " + sysTime.wDay;
            NativeMethods.MessageBox(IntPtr.Zero, dt, "Platform Invoke Sample", 0);

            Point p = new Point();
            p.x = 1;
            p.y = 2;
            p.z = 3;

          //  p.intValue = new IntValue(666);

            DoWithClass(p);
 
        }

        public delegate void CallFromNative(string cshapdata);

        [DllImport("__Internal", EntryPoint = "DoSomething")]
        static extern void DoSomething();

        [DllImport("__Internal", EntryPoint = "DoSomething2")]

        static extern void DoSomething2(string message);

        [DllImport("__Internal", EntryPoint = "DoSomething3")]
        static extern string DoSomething3(string message);

        [DllImport("__Internal", EntryPoint = "DoSomething4")]
        static extern void DoSomething4(CallFromNative d);

        [DllImport("__Internal", EntryPoint = "DoWithClass")]
        static extern void DoWithClass(Point d);

        [DllImport("__Internal", EntryPoint = "GetClassFromCpp")]
        static extern Point GetClassFromCpp();

        [DllImport("__Internal", EntryPoint = "GetClassFromCppRef")]
        static extern void GetClassFromCppRef(Point p);

        public static void PrintNum()
        {
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine("subTread num :  " + i);
                Thread.Sleep(100);
            }
        }

        public static void PrintNumInTimes(object times)
        {
            for (int i = 0; i < (int)times; i++)
            {
                Console.WriteLine("total : " + times + " subTread num :  " + i);
                Thread.Sleep(100);
            }
        }

        public void PrintNanme(object names)
        {
            for (int i = 0; i < (int)5; i++)
            {
                Console.WriteLine(" subTread name :  " + names);
                Thread.Sleep(100);
            }
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public class Point
    {
        public int x;
        public int y;
        public int z; 
       // public IntValue intValue;
    }

    [StructLayout(LayoutKind.Sequential)]
    public class IntValue
    {
       public int value;
        public IntValue(int a)
        {
            value = a;
        }

    }

    [StructLayout(LayoutKind.Sequential)]
    public class MySystemTime
    {
        public ushort wYear;
        public ushort wMonth;
        public ushort wDayOfWeek;
        public ushort wDay;
        public ushort wHour;
        public ushort wMinute;
        public ushort wSecond;
        public ushort wMilliseconds;
    }

    internal static class NativeMethods
    {
        [DllImport("Kernel32.dll")]
        internal static extern void GetSystemTime(MySystemTime st);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        internal static extern int MessageBox(
            IntPtr hWnd, string lpText, string lpCaption, uint uType);
    }
}