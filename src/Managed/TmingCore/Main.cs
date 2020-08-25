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
            int a = Add(1, 6);
        }

        public static int Add(int a, int b)
        {
            int c = a + b;
            return c;
        }
    }
}