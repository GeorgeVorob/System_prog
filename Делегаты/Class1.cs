using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Reflection;
using System.Text;

delegate double doubledeleg(double a);

namespace Делегаты
{
    class Class1
    {
        private Random rand = new Random();
        private doubledeleg Deleg;
        public doubledeleg[] arr = new doubledeleg[10];
        private string[] s = { "Method_dPlus2", "Method_dabs2", "Method_dSqrt", "Method_dDivide3", "Method_dminus1" };
        public void fill_array()
        {
            for (int i = 0; i < 10; i++)
            {
                int a;
                switch (a = rand.Next(5))
                {
                    case 0:
                        arr[i] = Method_dPlus2;
                        break;
                    case 1:
                        arr[i] = Method_dabs2;
                        break;
                    case 2:
                        arr[i] = Method_dSqrt;
                        break;
                    case 3:
                        arr[i] = Method_dDivide3;
                        break;
                    case 4:
                        arr[i] = Method_dminus1;
                        break;
                }
            }
        }
        private double Method_dPlus2(double d) { Console.WriteLine("Метод Method_dPlus2 "); Console.WriteLine("До исполнения:{0}", d.ToString()); return d + 2; }
        private double Method_dabs2(double d) { Console.WriteLine("Метод Method_dabs2 "); Console.WriteLine("До исполнения:{0}", d.ToString()); return d * d; }
        private double Method_dSqrt(double d) { Console.WriteLine("Метод Method_dSqrt "); Console.WriteLine("До исполнения:{0}", d.ToString()); return Math.Sqrt(d); }
        private double Method_dDivide3(double d) { Console.WriteLine("Метод Method_dDivide3 "); Console.WriteLine("До исполнения:{0}", d.ToString()); return d / 3; }
        private double Method_dminus1(double d) { Console.WriteLine("Метод Method_dminus1 "); Console.WriteLine("До исполнения:{0}", d.ToString()); return d - 1; }
    }
}