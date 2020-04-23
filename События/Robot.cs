using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace События
{
    class Robot
    {
        public delegate void MethodContainer();
        public event MethodContainer MoveDown;
        
        private int direction;
        private Random rnd = new Random();
        public void Move()
        {
            while(true)
            {
                direction = rnd.Next(4); //вверх, вправо, вниз, влево
                switch(direction)
                {
                    case 0:
                        Console.WriteLine("вверх");
                        break;
                    case 1:
                        Console.WriteLine("вправо");
                        break;
                    case 2:
                        Console.WriteLine("вниз");
                        MoveDown();
                        break;
                    case 3:
                        Console.WriteLine("влево");
                        break;
                }
                Thread.Sleep(300);
            }
        }
    }
}
