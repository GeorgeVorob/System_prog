using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Factory
{
    class Program
    {
        static void Main(string[] args)
        {

            (new Thread(() =>
            {
                AbsFactory FirstFactory = new FastFactory();
                AbsCar Fast_Car = FirstFactory.Create("Fcar");
                Fast_Car.Run(300);

            })).Start();

            AbsFactory Factory = new SlowFactory();
            AbsCar Slow_Car = Factory.Create("Scar");

            Slow_Car.Run(300);
            Console.ReadLine();
        }

    }



    abstract class AbsFactory
    {

        public AbsFactory()
        {

        }
        abstract public AbsCar Create(string name);
    }
    class FastFactory : AbsFactory
    {
        public FastFactory() : base()
        { }

        public override AbsCar Create(string name)
        {
            return new FastCar(name);
        }
    }
    class SlowFactory : AbsFactory
    {
        public SlowFactory() : base()
        { }

        public override AbsCar Create(string name)
        {
            return new SlowCar(name);
        }
    }

    abstract class AbsCar
    {
        public AbsCar(string name)
        {
        }
        abstract public void Run(int distance);
    }

    class FastCar : AbsCar
    {
        int speedcap = 70;
        int speed = 0;
        int acc = 7;
        int waittime = 1300;
        string Name;
        public FastCar(string name) : base(name)
        {
            Name = name;
            Console.WriteLine("Машина " + name + " создана");
        }
        public override void Run(int distance)
        {
            for (int i = 0; i < distance; i += speed)
            {
                Console.WriteLine("Машина " + Name + "; Скорость " + speed + "; оставшееся расстояние " + (distance - i).ToString());
                if (speed < speedcap) speed+=acc;
                Thread.Sleep(waittime);
            }
        }
    }
    class SlowCar : AbsCar
    {
        int speedcap = 50;
        int speed = 0;
        int acc = 5;
        int waittime = 3000;
        string Name;
        public SlowCar(string name) : base(name)
        {
            Name = name;
            Console.WriteLine("Машина " + name + " создана");
        }
        public override void Run(int distance)
        {
            for (int i = 0; i < distance; i += speed)
            {
                Console.WriteLine("Машина " + Name + "; Скорость " + speed + "; оставшееся расстояние " + (distance - i).ToString());
                if (speed < speedcap) speed += acc;
                Thread.Sleep(waittime);
            }
        }
    }
}
