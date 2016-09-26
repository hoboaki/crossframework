using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;

namespace CrossFramework
{
    class Program
    {
        static int Main(string[] args)
        {
            if (args.Length < 2)
            {// ˆø”‚ª‘«‚è‚È‚¢
                printUseage();
                return 0;
            }

            try
            {
                XDataConverter.Option option = new XDataConverter.Option();
                int index = 2;
                while (index < args.Length)
                {
                    string arg = args[index];
                    ++index;

                    if (arg == "-endian")
                    {
                        if (index == args.Length
                            || (args[index] != "BE" && args[index] != "LE")
                            )
                        {
                            errorWriteLine(arg + "'s argument is invalid.");
                            return -1;
                        }
                        option.OutputEndian = args[index] == "BE"
                            ? XDataConverter.Endian.Big
                            : XDataConverter.Endian.Little;
                        ++index;
                    }
                    else if (arg == "-encoding")
                    {
                        if (index == args.Length)
                        {
                            errorWriteLine(arg + "'s argument is invalid.");
                            return -1;
                        }
                        try
                        {
                            option.Encoding = Encoding.GetEncoding(args[index]);
                        }
                        catch( Exception )
                        {
                            errorWriteLine("Invalid encoding name '" + args[index] + "'.");
                            return -1;
                        }
                        ++index;
                    }
                    else if (arg == "-ignoreLabelNotFoundError")
                    {
                        option.IgnoreLabelNotFoundError = true;
                    }
                    else if (arg == "-silent")
                    {
                        option.IsSilent = true;
                    }
                    else
                    {
                        errorWriteLine("Unknown option '" + arg + "'.");
                        return -1;
                    }
                }

                XDataConverter.Convert(
                    new FileInfo(args[0])
                    , option
                    , new FileInfo(args[1])
                    );
            }
            catch (Exception exception)
            {
                errorWriteLine(exception.Message);
                return -1;
            }

            return 0;
        }

        static void errorWriteLine(string str)
        {
            System.Console.Error.WriteLine("Error: " + str);
        }

        static void printUseage()
        {
            Binarizer.PrintBanner();
            System.Console.WriteLine(@"Usage : XDataConverter.exe input_xml_filepath output_binary_filepath [option]");
            System.Console.WriteLine(@"Options :");
            System.Console.WriteLine(@"  -endian [BE|LE] -> Set binary endian. ");
            System.Console.WriteLine(@"    BE : Big Endian");
            System.Console.WriteLine(@"    LE : Little Endian(Default)");
            System.Console.WriteLine(@"  -encoding [EncodeWebName] -> Set string encode format. ");
            System.Console.WriteLine(@"    For exmaple , 'utf-8' , 'shift_jis'. ");
            System.Console.WriteLine(@"    Default is 'utf-8'.");
            System.Console.WriteLine(@"  -ignoreLabelNotFoundError -> Ignore label not found error. ");
            System.Console.WriteLine(@"  -silent -> Don't print standard output. ");
        }

    }
}
