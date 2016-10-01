using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace CppCodeModifier
{
    class Program
    {
        static void Main(string[] args)
        {
            // ファイルに対して操作
            string libraryDirPath = "../../../../Library";
            var filePaths = new List<string>();
            var cppFileList = new List<string>();
            var cFileList = new List<string>();
            var cppFiles = Directory.EnumerateFiles(libraryDirPath, "*.cpp", SearchOption.AllDirectories);
            var hppFiles = Directory.EnumerateFiles(libraryDirPath, "*.hpp", SearchOption.AllDirectories);
            var cFiles = Directory.EnumerateFiles(libraryDirPath, "*.c", SearchOption.AllDirectories);
            var hFiles = Directory.EnumerateFiles(libraryDirPath, "*.h", SearchOption.AllDirectories);
            var mFiles = Directory.EnumerateFiles(libraryDirPath, "*.m", SearchOption.AllDirectories);
            cppFileList.AddRange(cppFiles);
            cppFileList.AddRange(hppFiles);
            cFileList.AddRange(cFiles);
            cFileList.AddRange(hFiles);
            filePaths.AddRange(cppFileList);
            filePaths.AddRange(cFileList);
            filePaths.AddRange(mFiles);
            var textEditFunc = new Action<List<string>, Func<List<string>, bool>>((paths, func) =>
            {
                foreach (var path in paths)
                {
                    var lines = File.ReadAllLines(path).ToList();
                    if (func(lines))
                    {
                        File.WriteAllLines(path, lines);
                        Console.WriteLine(String.Format("Modify: {0}", path));
                    }
                }
            });

            // 先頭のコメントを変更
            if (true)
            {
                textEditFunc(filePaths,
                    (lines) =>
                    {
                        if (lines[0].Contains("/**") && lines[4].Contains("*/"))
                        {
                            // 5行消す
                            lines.RemoveRange(0, 5);
                            // 1行追加
                            lines.Insert(0, "// 文字コード：UTF-8");
                            return true;
                        }
                        return false;
                    }
                    );
            }

            // ブロックコメントをラインコメントに
            if (true)
            {
                textEditFunc(filePaths,
                    (lines) =>
                    {
                        bool isModify = false;
                        bool inBlock = false;
                        string prefix = "";
                        var result = lines.ToList();
                        result.Clear();
                        for (int i = 0; i < lines.Count; ++i)
                        {
                            var line = lines[i];
                            if (!inBlock)
                            {
                                if (i != 0 && line.Trim().StartsWith("/**"))
                                {
                                    inBlock = true;
                                    prefix = line.Substring(0, line.IndexOf("/**"));
                                }
                                else
                                {
                                    result.Add(line);
                                }
                            }
                            else
                            {
                                if (line.Trim().StartsWith("*/"))
                                {
                                    inBlock = false;
                                    isModify = true;
                                }
                                else
                                {
                                    int idx = line.IndexOf(" * ");
                                    if (idx < 0)
                                    {
                                        result.Add(prefix + "/// " + line);
                                    }
                                    else
                                    {
                                        result.Add(line.Substring(0, idx) + "/// " + line.Substring(idx + 3));
                                    }
                                }
                            }
                        }

                        if (isModify)
                        {
                            lines.Clear();
                            lines.AddRange(result);
                        }
                        return isModify;
                    }
                    );
            }

            // 末尾
            if (true)
            {
                textEditFunc(cppFileList,
                    (lines) =>
                    {
                        // hpp
                        {
                            int eofIndex = lines.Count - 1;
                            int endIf = eofIndex - 1;
                            int endComment = endIf - 1;
                            int endKakko = endComment - 1;
                            if (lines[eofIndex].Contains("EOF") &&
                                lines[endIf].Contains("endif") &&
                                lines[endKakko].StartsWith("}") &&
                                lines[endComment].StartsWith("//--")
                                )
                            {
                                lines.RemoveAt(endKakko);
                                lines.Insert(endKakko, "} // namespace");
                                lines.RemoveAt(endComment);
                                lines.Insert(endKakko, "");
                                return true;
                            }
                        }
                        // cpp
                        {
                            int eofIndex = lines.Count - 1;
                            int endComment = eofIndex - 1;
                            int endKakko = endComment - 1;
                            int endComment2 = endKakko - 1;
                            if (lines[eofIndex].Contains("EOF") &&
                                lines[endComment].StartsWith("//--") &&
                                lines[endKakko].StartsWith("}") &&
                                lines[endComment2].StartsWith("//--")
                                )
                            {
                                lines.RemoveAt(endKakko);
                                lines.Insert(endKakko, "} // namespace");
                                lines.RemoveAt(endComment);
                                lines.RemoveAt(endComment2);
                                return true;
                            }
                        }
                        return false;
                    }
                    );
            }

            // 80セパレータ
            if (true)
            {
                textEditFunc(filePaths,
                    (lines) =>
                    {
                        bool isModify = false;
                        for (int i = 0; i < lines.Count; ++i)
                        {
                            var line = lines[i];
                            if (line.Trim().StartsWith("//----------------------------------------------------------"))
                            {
                                string prefix = line.Substring(0, line.IndexOf("//"));
                                lines.RemoveAt(i);
                                lines.Insert(i, prefix + "//------------------------------------------------------------------------------");
                                isModify = true;
                            }
                        }
                        return isModify;
                    }
                    );
            }
        }
    }
}
