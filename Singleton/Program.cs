using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Singleton
{
    class Singleton
    {
        private static Singleton instance; //Ссылка на экземпляр

        public string Name { get; set; }
        private static object syncRoot = new Object();

        protected Singleton()
        {
        }

        public static Singleton getInstance()
        {
            if (instance == null)
            {
                lock (syncRoot)
                {
                    if (instance == null)
                        instance = new Singleton();
                }
            }
            return instance;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Singleton S1 = Singleton.getInstance();
            S1.Name = "value 1";
            Singleton S2 = Singleton.getInstance();
            Console.WriteLine(S2.Name);
            Console.WriteLine("Значение переменной во втором экземпляре класса то же, что и в первом, т.к. они ссылаются на один и тот же экземпляр");
            Console.ReadKey();
        }
    }
}
