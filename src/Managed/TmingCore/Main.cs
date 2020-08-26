using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TmingCore
{
    public class Main
    {
        public static void Start()
        {
            Console.WriteLine("TmingEngine core start success");
            Console.WriteLine("TmingEngine core start do something else");
            int a = Add(1, 8);
            Console.WriteLine("a: "+a);
            int i = 1;
            while (true)
            {               
                int j = i + 1;

                i =j;
                if (i > 100)
                {
                    break;
                }
            }
            Console.WriteLine("I: " + i);
        }

        public static int Add(int a, int b)
        {
            int c = a + b;
            return c;
        }
    }
}