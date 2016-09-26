using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;
using CrossFramework.XG3D;

namespace CrossFramework.TGAConverter
{
    class Program
    {
        static int Main(string[] args)
        {
            // 引数チェック
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: TGAConverter.exe input_tga_path output_xml_path [options]");
                Console.WriteLine(@"Options :");

                string format = "";
                foreach ( var formatType in Enum.GetValues(typeof(XG3D.ResTex.FormatType)) )
                {
                    if ( format.Length == 0 )
                    {
                        format += formatType.ToString();
                    }
                    else
                    {
                        format += "|" + formatType.ToString();
                    }
                }
                Console.WriteLine(@"  -format [" + format + "]");
                Console.WriteLine(@"    default: RGBA8");
                return -1;
            }

            // ファイルパス
            FileInfo tgaFileInfo = new FileInfo(args[0]);
            FileInfo xmlFileInfo = new FileInfo(args[1]);

            // オプション解析
            XG3D.ResTex.FormatType optFormatType = XG3D.ResTex.FormatType.RGBA8;
            {
                int index = 2;
                while (index < args.Length)
                {
                    string arg = args[index];
                    ++index;

                    if (arg == "-format")
                    {
                        try
                        {
                            if (index == args.Length)
                            {
                                throw new Exception();
                            }
                            optFormatType = (XG3D.ResTex.FormatType)Enum.Parse(typeof(XG3D.ResTex.FormatType), args[index]);
                        }
                        catch (Exception)
                        {
                            errorWriteLine("'" + arg + "'s argument is invalid.");
                            return -1;
                        }
                        ++index;
                    }
                    else
                    {
                        errorWriteLine("Unknown option '" + arg + "'.");
                        return -1;
                    }
                }
            }


            // 処理
            try
            {
                // 読み込み
                TGAImage tga = TGAImage.FromFilePath(tgaFileInfo.FullName);

                // 変換
                XG3D.ResTex res = XG3D.ResTex.FromImage(
                    tga.Image
                    , optFormatType
                    , tgaFileInfo.Name.Substring(0, tgaFileInfo.Name.Length - tgaFileInfo.Extension.Length)
                    );

                // 書き込み
                res.WriteXml(xmlFileInfo.FullName);
            }
            catch (Exception exp)
            {
                System.Console.Error.WriteLine(exp.Message);
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
}
