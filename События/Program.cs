using System;
using System.Threading;

namespace События
{
    class Program
    {
        static void Main(string[] args)
        {
            Handler H = new Handler();
            Robot R = new Robot();
            R.MoveDown += H.Trigger;
            Thread myThread = new Thread(new ThreadStart(R.Move));
            myThread.Start();
        }
    }
}
