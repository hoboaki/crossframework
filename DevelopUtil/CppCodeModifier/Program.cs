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
            var cppFilePaths = new List<string>();
            cppFilePaths.AddRange(Directory.EnumerateFiles(libraryDirPath, "*.cpp", SearchOption.AllDirectories));
            cppFilePaths.AddRange(Directory.EnumerateFiles(libraryDirPath, "*.hpp", SearchOption.AllDirectories));
            filePaths.AddRange(Directory.EnumerateFiles(libraryDirPath, "*.c", SearchOption.AllDirectories));
            filePaths.AddRange(Directory.EnumerateFiles(libraryDirPath, "*.h", SearchOption.AllDirectories));
            filePaths.AddRange(Directory.EnumerateFiles(libraryDirPath, "*.m", SearchOption.AllDirectories));
            filePaths.AddRange(cppFilePaths);
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
        }
    }
}
