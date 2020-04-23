using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace События
{
    class Handler
    {
        int count = 0;
        public void Trigger()
        {
            count++;
            Console.WriteLine("Робот ещё раз пошёл вниз");
            using (StreamWriter sw = new StreamWriter("../../../count.txt", false, System.Text.Encoding.Default))
            {
                sw.WriteLine("Робот пошёл вниз "+count.ToString()+" раз.");
            }

        }
    }
}
