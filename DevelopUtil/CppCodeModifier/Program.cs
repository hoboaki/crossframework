using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Text.RegularExpressions;
using System.Runtime.InteropServices;
using System.Net.Http.Headers;

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
            if (false)
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
            if (false)
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
            if (false)
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
            if (false)
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

            // hpp
            if (false)
            {
                textEditFunc(hppFiles.ToList(),
                    (lines) =>
                    {
                        bool isModify = false;
                        // 最後のnamespaceのindex
                        int lastNamespaceIndex = lines.FindLastIndex(x => x.StartsWith("namespace "));
                        int lastSeparatorIndex = lines.Count - 1;
                        while (0 <= lastSeparatorIndex)
                        {
                            lastSeparatorIndex = lines.FindLastIndex(lastSeparatorIndex, x => x == "//------------------------------------------------------------------------------");
                            if (lastSeparatorIndex < 0)
                            {
                                break;
                            }

                            if (lastSeparatorIndex + 1 == lastNamespaceIndex)
                            {
                                // namespace の後に空行があるかどうかチェック
                                if (lines[lastNamespaceIndex + 1].Trim().Length != 0)
                                {
                                    lines.Insert(lastNamespaceIndex + 1, "");
                                    isModify = true;
                                }
                            }
                            else
                            {
                                lines.RemoveAt(lastSeparatorIndex);
                                isModify = true;
                            }

                            --lastSeparatorIndex;
                        }

                        // コメントのインデントをなおす
                        for (int baseIdx = lines.Count - 1; 0 < baseIdx; --baseIdx)
                        {
                            string[] keywords = { "class", "enum", "struct", "typedef" };
                            bool isTargetLine = false;
                            foreach (var keyword in keywords)
                            {
                                if (lines[baseIdx].StartsWith(keyword))
                                {
                                    isTargetLine = true;
                                    break;
                                }
                            }

                            if (isTargetLine)
                            {
                                int idx = baseIdx - 1;
                                while (lines[idx].StartsWith("    "))
                                {
                                    var newLine = lines[idx].Trim();
                                    lines.RemoveAt(idx);
                                    lines.Insert(idx, newLine);
                                    isModify = true;
                                }
                            }


                        }

                        return isModify;
                    }
                    );
            }

            // cpp
            if (false)
            {
                textEditFunc(cppFiles.ToList(),
                    (lines) =>
                    {
                        bool isModify = false;
                        // 最後のnamespaceのindex
                        int lastNamespaceIndex = lines.FindLastIndex(x => x.StartsWith("namespace "));
                        int lastSeparatorIndex = lines.Count - 1;
                        while (0 <= lastSeparatorIndex)
                        {
                            lastSeparatorIndex = lines.FindLastIndex(lastSeparatorIndex, x => x == "//------------------------------------------------------------------------------");
                            if (lastSeparatorIndex < 0)
                            {
                                break;
                            }

                            if (lastSeparatorIndex + 1 == lastNamespaceIndex)
                            {
                                // namespace の後に空行があるかどうかチェック
                                if (lines[lastNamespaceIndex + 1].Trim().Length != 0)
                                {
                                    lines.Insert(lastNamespaceIndex + 1, "");
                                    isModify = true;
                                }
                            }
                            else
                            {
                                isModify = true;
                            }

                            --lastSeparatorIndex;
                        }

                        // コメントのインデントをなおす
                        for (int baseIdx = lines.Count - 1; 0 < baseIdx; --baseIdx)
                        {
                            string[] keywords = { "class", "enum", "struct", "typedef" };
                            bool isTargetLine = false;
                            foreach (var keyword in keywords)
                            {
                                if (lines[baseIdx].StartsWith(keyword))
                                {
                                    isTargetLine = true;
                                    break;
                                }
                            }

                            if (isTargetLine)
                            {
                                int idx = baseIdx - 1;
                                while (lines[idx].StartsWith("    "))
                                {
                                    var newLine = lines[idx].Trim();
                                    lines.RemoveAt(idx);
                                    lines.Insert(idx, newLine);
                                    isModify = true;
                                }
                            }
                        }

                        // コンストラクタのインデント位置をなおす
                        bool inMemberInitilizer = false;
                        for (int baseIdx = 0; baseIdx < lines.Count; ++baseIdx)
                        {
                            if (inMemberInitilizer)
                            {
                                if (!lines[baseIdx].StartsWith("    "))
                                {
                                    inMemberInitilizer = false;
                                }
                                else
                                {
                                    var line = lines[baseIdx].Substring(4);
                                    lines.RemoveAt(baseIdx);
                                    lines.Insert(baseIdx, line);
                                }
                            }
                            else if (lines[baseIdx].StartsWith("    : "))
                            {
                                if (lines[baseIdx - 1].IndexOf(" ") != 0 || lines[baseIdx - 1].Trim() == ")")
                                {
                                    inMemberInitilizer = true;
                                    var line = lines[baseIdx].Substring(4);
                                    lines.RemoveAt(baseIdx);
                                    lines.Insert(baseIdx, line);
                                    isModify = true;
                                }
                            }
                        }

                        // 終端括弧位置をなおす
                        for (int baseIdx = 0; baseIdx < lines.Count; ++baseIdx)
                        {
                            var line = lines[baseIdx];
                            if (line.Trim() == ")" || line.Trim() == ");")
                            {
                                int len = lines[baseIdx - 1].Length - lines[baseIdx - 1].Trim().Length;
                                string prefix = "";
                                for (int i = 0; i < len; ++i)
                                {
                                    prefix += " ";
                                }
                                lines.RemoveAt(baseIdx);
                                lines.Insert(baseIdx, prefix + line.Trim());
                                isModify = true;
                            }
                        }

                        // カンマ位置修正
                        for (int baseIdx = 0; baseIdx < lines.Count; ++baseIdx)
                        {
                            var line = lines[baseIdx];
                            if (line.StartsWith(" ") && line.Trim().StartsWith(", "))
                            {
                                int len = line.IndexOf(",");
                                string prefix = "";
                                for (int i = 0; i < len; ++i)
                                {
                                    prefix += " ";
                                }
                                {
                                    int i = baseIdx;
                                    while (lines[i].Trim().StartsWith(","))
                                    {
                                        var newLine = lines[i];
                                        lines.RemoveAt(i);
                                        lines.Insert(i, prefix + newLine.Trim().Substring(2));
                                        --i;
                                        newLine = lines[i];
                                        if (newLine.Contains(" //"))
                                        {
                                            int cmtIdx = newLine.IndexOf(" //");
                                            newLine = newLine.Substring(0, cmtIdx) + "," + newLine.Substring(cmtIdx);
                                        }
                                        else
                                        {
                                            newLine += ",";
                                        }
                                        lines.RemoveAt(i);
                                        lines.Insert(i, newLine);
                                    }
                                }
                            }
                        }

                        return isModify;
                    }
                    );
            }

            // 括弧位置警告
            if (false)
            {
                Console.WriteLine("KakkoCheck: ");
                textEditFunc(cppFiles.ToList(),
                    (lines) =>
                    {
                        bool isModify = false;
                        for (int i = 1; i < lines.Count; ++i)
                        {
                            var prevLine = lines[i - 1];
                            var line = lines[i];
                            if (0 <= line.LastIndexOf(")") &&
                                line.LastIndexOf(")") == prevLine.LastIndexOf(")")
                                )
                            {
                                if (!prevLine.Contains(";") && line.Trim().Length <= 2)
                                {
                                    Console.WriteLine("Line: " + i);
                                    isModify = true;
                                }
                            }
                        }
                        return isModify;
                    }
                    );
            }

            // 同行開始括弧位置警告
            if (false)
            {
                Console.WriteLine("BeginKakkoCheck: ");
                textEditFunc(cppFiles.ToList(),
                    (lines) =>
                    {
                        bool isModify = false;
                        for (int i = 0; i < lines.Count; ++i)
                        {
                            var line = lines[i];

                            string[] keywords = { " if ", " for ", " while ", " switch" };
                            bool isTargetLine = false;
                            foreach (var keyword in keywords)
                            {
                                if (line.Contains(keyword))
                                {
                                    isTargetLine = true;
                                    break;
                                }
                            }

                            if (isTargetLine)
                            {
                                if (!line.Contains("{") && lines[i + 1].Contains("{"))
                                {
                                    var nextLine = lines[i + 1];
                                    var newLine = line;
                                    if (nextLine.Contains("//"))
                                    {
                                        // コメントだけさらに次の行へ
                                        int idx = nextLine.IndexOf("//");
                                        string prefix = "";
                                        for (int c = 0; c < nextLine.IndexOf("{"); ++c)
                                        {
                                            prefix += " ";
                                        }
                                        lines.Insert(i + 2, prefix + "    " + nextLine.Substring(idx));
                                        lines.RemoveAt(i + 1);
                                        lines.Insert(i + 1, nextLine.Substring(0, idx));
                                        nextLine = lines[i + 1];
                                    }

                                    lines.RemoveAt(i);
                                    if (!newLine.Contains("//"))
                                    {
                                        newLine += " " + nextLine.Trim();
                                    }
                                    else
                                    {
                                        int cmtIdx = newLine.IndexOf("//");
                                        newLine = newLine.Substring(0, cmtIdx) + nextLine.Trim() + newLine.Substring(cmtIdx);
                                    }
                                    lines.Insert(i, newLine);
                                    lines.RemoveAt(i + 1);
                                    isModify = true;
                                }
                            }
                        }
                        return isModify;
                    }
                    );
            }

            // include直前のセパレータ削除
            if (false)
            {
                textEditFunc(cppFiles.ToList(),
                    (lines) =>
                    {
                        bool isModify = false;
                        for (int i = 1; i < lines.Count; ++i)
                        {
                            var line = lines[i];
                            if (line.StartsWith("#include") && lines[i - 1].StartsWith("//-------"))
                            {
                                lines.RemoveAt(i - 1);
                                isModify = true;
                                break;
                            }
                        }
                        return isModify;
                    });

            }

            // mHoge -> hoge_
            if (false)
            {
                textEditFunc(cppFileList,
                    (lines) =>
                    {
                        string evaluator(Match m)
                        {
                            return m.Groups[1].Value + m.Groups[2].Value.ToLower() + m.Groups[3].Value + "_";
                        };
                        bool isModify = false;
                        for (int i = 0; i < lines.Count; ++i)
                        {
                            var line = lines[i];
                            var newLine = Regex.Replace(line, @"(\W)m([A-Z])([\w\d]*)", evaluator);
                            if (line != newLine)
                            {
                                lines.Insert(i, newLine);
                                lines.RemoveAt(i + 1);
                                isModify = true;
                            }
                        }
                        return isModify;
                    });
            }

            // hoge() -> Hoge()
            if (false)
            {
                string evaluator(Match m)
                {
                    var str = (m.Groups[2].Value + m.Groups[3].Value);
                    str = str.Substring(0, str.Length - 1);
                    if (m.Groups[1].Value == "std::")
                    {
                        return m.Value;
                    }
                    switch (str)
                    {
                        case "defined":
                        case "warning":
                        case "if":
                        case "for":
                        case "while":
                        case "bool":
                        case "static_assert":
                        case "int":
                        case "uint":
                        case "float":
                        case "sizeof":
                        case "new":
                        case "delete":
                        case "operator":
                        case "template":
                        case "static_cast":
                        case "reinterpret_cast":
                        case "infinity":
                        case "assert":
                        case "va_start":
                        case "va_end":
                        case "vsnprintf":
                        case "vswprintf":
                        case "func":
                        case "vec":
                        case "newMin":
                        case "newTerm":
                        case "u16":
                        case "u32":
                        case "u64":
                        case "f32":
                        case "s16":
                        case "s32":
                        case "s64":
                            return m.Value;
                    }
                    if (str.EndsWith("_") || str.EndsWith("_t"))
                    {
                        return m.Value;
                    }
                    if (0 < m.Groups[3].Value.Length && char.IsUpper(m.Groups[3].Value[0]))
                    {
                        return m.Value;
                    }
                    return m.Groups[1].Value + m.Groups[2].Value.ToUpper() + m.Groups[3].Value;
                };
                textEditFunc(cppFileList,
                    (lines) =>
                    {
                        bool isModify = false;
                        for (int i = 0; i < lines.Count; ++i)
                        {
                            var line = lines[i];
                            var newLine = Regex.Replace(line, @"(\&|\!|\(|std::|::|\.|\s|->)([a-z])(\w+\(|\w+\<)", evaluator);
                            if (line != newLine)
                            {
                                lines.Insert(i, newLine);
                                lines.RemoveAt(i + 1);
                                isModify = true;
                            }
                        }
                        return isModify;
                    });
            }

            // aHoge -> hoge
            if (false)
            {
                textEditFunc(cppFileList,
                    (lines) =>
                    {
                        string evaluator(Match m)
                        {
                            return m.Groups[1].Value + m.Groups[2].Value.ToLower() + m.Groups[3].Value;
                        };
                        bool isModify = false;
                        for (int i = 0; i < lines.Count; ++i)
                        {
                            var line = lines[i];
                            var newLine = Regex.Replace(line, @"(\W)a([A-Z])([\w\d]*)", evaluator);
                            if (line != newLine)
                            {
                                lines.Insert(i, newLine);
                                lines.RemoveAt(i + 1);
                                isModify = true;
                            }
                        }
                        return isModify;
                    });
            }


        }
    }
}
