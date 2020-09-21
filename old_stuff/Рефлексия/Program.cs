using System;
using System.Reflection;

namespace Рефлексия
{
    class Program
    {
        static void Main(string[] args)
        {

            Assembly Asm = Assembly.LoadFrom("../../bavito_server.exe");
            Console.WriteLine("exe файл взят с https://github.com/GeorgeVorob/bavito-server");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine(Asm.FullName);
            Type[] types = Asm.GetTypes();
            foreach (Type Types in types)
            {
                Console.ForegroundColor = ConsoleColor.White;
                Console.Write("Тип данных: ");
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine(Types.Name);
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine($"Методы: ");
                Console.ForegroundColor = ConsoleColor.Green;
                foreach (MethodInfo Methods in Types.GetMethods())
                {
                    Console.WriteLine($"   {Methods}\n");
                }
                Console.ResetColor();
                Console.WriteLine();
            }
            Console.WriteLine("Нажмите любую клавишу для закрытия");
            Console.Read();
        }
    }
}