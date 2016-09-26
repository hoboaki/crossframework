using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Collada141;
using CrossFramework.XG3D;

namespace DAEConverter
{
    class Program
    {
        static int Main(string[] args)
        {
            // 引数チェック
            if (args.Length < 1)
            {
                Console.WriteLine("Usage: DAEConverter.exe input_xml_path [commands]");
                Console.WriteLine(@"Commands :");
                Console.WriteLine(@"  -xmdl 'output_xml_path'");
                Console.WriteLine(@"  -xmdl 'visual_scene_name;output_xml_path'");
                Console.WriteLine(@"    Output xmdl file.");
                Console.WriteLine(@"    ex1. If you want to convert first visual_scene.");
                Console.WriteLine(@"      -xmdl 'Output.xmdl'");
                Console.WriteLine(@"    ex2. If you want to convert visual_scene named 'BG'.");
                Console.WriteLine(@"      -xmdl 'BG;Output.xmdl'");
                return -1;
            }

            // ファイルパス
            FileInfo xmlFileInfo = new FileInfo(args[0]);

            // Collada読み込み
            COLLADA dae = null;
            try
            {
                dae = COLLADA.Load(xmlFileInfo.FullName);
            }
            catch (Exception exp)
            {
                errorWriteLine(exp);
                return -1;
            }

            // オプション解析
            {
                int index = 1;
                while (index < args.Length)
                {
                    string arg = args[index];
                    ++index;

                    if (arg == "-xmdl")
                    {// モデル出力
                        // 名前＆パス決定
                        string visualSceneName = "";
                        string outputPath = "";
                        try
                        {
                            if (index == args.Length)
                            {
                                throw new Exception();
                            }

                            // 引数解析
                            outputPath = args[index];
                            if (0 <= outputPath.IndexOf(';'))
                            {
                                visualSceneName = outputPath.Split(';')[0];
                                outputPath =  outputPath.Substring( visualSceneName.Length + 1 );
                            }                            
                        }
                        catch (Exception)
                        {
                            errorWriteLine("'" + arg + "'s argument is invalid.");
                            return -1;
                        }
                        ++index;

                        // 出力
                        try
                        {
                            // インデックス値の選択
                            int visualSceneIndex = 0;
                            if (0 < visualSceneName.Length)
                            {
                                foreach (var item in dae.Items)
                                {
                                    library_visual_scenes visualScenes = item as library_visual_scenes;
                                    if (visualScenes == null)
                                    {
                                        continue;
                                    }

                                    bool isFound = false;
                                    int idx = 0;
                                    foreach (var visualScene in visualScenes.visual_scene)
                                    {
                                        if (visualScene.name == visualSceneName)
                                        {
                                            visualSceneIndex = idx;
                                            isFound = true;
                                            break;
                                        }
                                        ++idx;
                                    }

                                    if (!isFound)
                                    {
                                        errorWriteLine("Not found visual_scene named '" + visualSceneName + "'.");
                                        return -1;
                                    }
                                    break;
                                }
                            }

                            // ResMdl作成
                            CrossFramework.XG3D.ResMdl resMdl = CrossFramework.XG3D.ResMdl.FromDAE(dae, visualSceneIndex);

                            // XML出力
                            resMdl.WriteXml(outputPath);

                            // テストで読み込んでみてスキーマ通りかチェックする
#if DEBUG
                            ResMdl.FromXml(outputPath);
#endif
                        }
                        catch (Exception exp)
                        {
                            errorWriteLine(exp);
                            return -1;
                        }
                    }
                    else
                    {
                        errorWriteLine("Unknown option '" + arg + "'.");
                        return -1;
                    }
                }
            }

            // 成功
            return 0;
        }

        //------------------------------------------------------------
        static void errorWriteLine(string str)
        {
            System.Console.Error.WriteLine("Error: " + str);
        }
        static void errorWriteLine(Exception exp)
        {
            errorWriteLine(exp.Message);
            errorWriteLine(exp.ToString());
            System.Console.Error.WriteLine(exp.StackTrace.ToString());
        }
    }
}
