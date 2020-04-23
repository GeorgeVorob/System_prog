using System;
using Extenshion_methods;

namespace Extenshion_methods
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                int number;
                Console.WriteLine("Enter number...");
                number = Int32.Parse(Console.ReadLine());
                if (number.IsPalindrome()) Console.WriteLine("Entered number is a palindrome");
                else Console.WriteLine("Entered number is not a palindrome");
            }
            catch(System.FormatException)
            {
                Console.WriteLine("Incorrect number format!");
            }
        }
    }
}
