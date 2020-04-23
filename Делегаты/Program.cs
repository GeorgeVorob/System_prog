using System;

namespace Делегаты
{
    class Program
    {
        static void Main(string[] args)
        {
            double variable = 5;
            Class1 C = new Class1();
            for (int i = 0; i < 4; i++)
            {
                C.fill_array();
                for (int j = 0; j < 10; j++)
                {
                    variable = C.arr[j].Invoke(variable);
                }
            }
        }
    }
}