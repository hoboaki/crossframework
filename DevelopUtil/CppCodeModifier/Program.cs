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
        }
    }
}
