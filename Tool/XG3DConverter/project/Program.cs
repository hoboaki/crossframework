using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using CrossFramework.XG3D;
using CrossFramework;
using System.Xml;

namespace CossFramework.XG3DConverter
{
    class Program
    {
        static int Main(string[] args)
        {
            // 引数解析
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: XG3DConverter.exe output_bin_path [option] input_xml_path...");
                Console.WriteLine(@"Options :");
                Console.WriteLine(@"  -platform [WIN|MAC|IOS] -> Set binary target engine. ");
                Console.WriteLine(@"    WIN : Windows(Default)");
                Console.WriteLine(@"    MAC : MacOSX");
                Console.WriteLine(@"    IOS : iOS");
                Console.WriteLine(@"  -endian [BE|LE] -> Set binary endian. ");
                Console.WriteLine(@"    BE : Big Endian");
                Console.WriteLine(@"    LE : Little Endian(Default)");
                Console.WriteLine(@"  -encoding [EncodeWebName] -> Set string encode format. ");
                Console.WriteLine(@"    For exmaple , 'utf_8' , 'shift_jis'. ");
                Console.WriteLine(@"    Default is 'utf_8'.");
                return -1;
            }
            FileInfo binPath = new FileInfo(args[0]);
            List<FileInfo> xmlPaths = new List<FileInfo>();

            // オプション解析
            CrossFramework.XG3D.BinarizeOption option = new BinarizeOption();
            {
                int index = 1;
                while (index < args.Length)
                {
                    string arg = args[index];
                    ++index;
                    
                    if (arg == "-platform")
                    {
                        try
                        {
                            if (index == args.Length)
                            {
                                throw new Exception();
                            }
                            switch ((Platform)Enum.Parse(typeof(Platform), args[index]))
                            {
                            case Platform.WIN:
                            case Platform.MAC:
                                option.TargetEngine = Engine.GL;
                                break;

                            case Platform.IOS:
                                option.TargetEngine = Engine.GLES;
                                break;
                            }
                        }
                        catch (Exception)
                        {
                            errorWriteLine(arg + "'s argument is invalid.");
                            return -1;
                        }
                        ++index;
                    }
                    else if (arg == "-endian")
                    {
                        if (index == args.Length
                            || (args[index] != "BE" && args[index] != "LE")
                            )
                        {
                            errorWriteLine(arg + "'s argument is invalid.");
                            return -1;
                        }
                        option.Endian = args[index] == "BE"
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
                        catch (Exception)
                        {
                            errorWriteLine("Invalid encoding name '" + args[index] + "'.");
                            return -1;
                        }
                        ++index;
                    }
                    else
                    {
                        xmlPaths.Add(new FileInfo(arg));
                    }
                }
            }

            // 変換
            try
            {
                // 各XMLファイルをResFileに突っ込む
                ResBin resFile = new ResBin();
                foreach (var xmlPath in xmlPaths)
                {
                    // XMLロード
                    XmlDocument xml = new XmlDocument();
                    xml.Load(xmlPath.FullName);

                    // ドキュメントの要素名で分岐
                    string rootName = xml.DocumentElement.Name;
                    if (rootName == "xmdl")
                    {// xmdl
                        resFile.Add(ResMdl.FromXml(xml, xmlPath));
                    }
                    else if (rootName == "xtex")
                    {// xtex
                        resFile.Add(ResTex.FromXml(xml, xmlPath));
                    }
                    else
                    {// 不明
                        throw new Exception("'" + xmlPath.FullName + "' は未対応のXMLファイルです。");
                    }
                }
                
                // バイナリ化して出力
                File.WriteAllBytes(binPath.FullName, resFile.ToArray(option));
            }
            catch (Exception exp)
            {
                Console.Error.WriteLine(exp.Message);
                Console.Error.WriteLine(exp.StackTrace);
                return -1;
            }            

            // 成功
            return 0;
        }

        //------------------------------------------------------------
        static void errorWriteLine(string str)
        {
            System.Console.Error.WriteLine("Error: " + str);
        }
    }
    //------------------------------------------------------------
    enum Platform
    {
        WIN,
        MAC,
        IOS,
    };
}
