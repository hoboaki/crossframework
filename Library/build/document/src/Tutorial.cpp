/**
@page Tutorial チュートリアル
- @subpage TutorialMSVC
- @subpage TutorialXCode-OSX

@page TutorialMSVC Windows - Microsoft VisualC++ 2010 ExpressEdition
MSVC2010を使ってCrossFramework用プロジェクトファイルを作成する方法を説明します。@n
ここではcrossframeworkディレクトリが c:/ に設置されているとします。

1. 新規プロジェクト作成
- 新しいプロジェクトを作成します。
@image html start_msvc_newproject.png
- Win32 コンソールアプリケーションとして作成します。
@image html start_msvc_newproject_wizard.png
- ウィザード画面は次へを押してください。
@image html start_msvc_newproject_detail.png
- 「プリコンパイル済みヘッダー」のチェックを外して「完了」を実行してください。
- （※プリコンパイル済みヘッダーを使う例はややこしいため、ここでは使用しない方法を説明しています。）
- 以上で新規プロジェクト作成作業は終了です。

2. 参照設定
- CrossFrameworkのプロジェクトファイルを参照するように設定します。
@image html start_msvc_addproject.png
- 「ファイル」「追加」「既存のプロジェクト」を選択し、「C:/crossframework/Library/build/library/windows/XBase.vcxproj」を追加してください。
@image html start_msvc_refproject.png
- 作成したプロジェクトを「右クリック」「参照」「新しい参照を追加」からXBaseを追加してください。
@image html start_msvc_include.png
- 「構成プロパティ」「C/C++」「全般」「追加のインクルードディレクトリ」に「C:/crossframework/Library/include」を追加してください。
@image html start_msvc_preprocessor.png
- 「構成プロパティ」「C/C++」「全般」「プリプロセッサ」「プリプロセッサの定義」に「XLIBRARY_DEBUG」を追加してください。
- （＊指定するプリプロセッサについて詳しく知りたい型は @ref AboutBuildVersion をご覧ください。）
- 以上で参照設定は終了です。
- （＊ここではXBaseしか参照設定しませんでしたが、AeG3dなど他のプロジェクトを参照するときも同様に設定してください。）

3. プログラム記述
- 試しにウィンドウを表示させるプログラムを記述します。
@image html start_msvc_cpp.png
- デモのソースコード「C:/crossframework/Library/build/demo/src/XBase/display/Main.cpp」の内容をコピー＆ペーストします。
@image html start_msvc_run.png
- ビルドして実行するとウィンドウが表示されます。


以上でチュートリアルは終了です。お疲れ様でした。 @n
なお、このプログラムはWindows以外にもMacOSX、iOSで動作します。@n
@n
その他のプログラムを書く場合は  @ref DemoList のソースコードを参考にしてください。@n

@page TutorialXCode-OSX MacOSX - XCode3
XCodeを使ってCrossFramework用プロジェクトファイルを作成する方法を説明します。@n
MacOSX用のプロジェクトファイルの作り方を説明しますがiOS用もほぼ同じ方法で作成できます。 @n
ここではcrossframeworkディレクトリが Desktop に設置されているとします。 @n

1. 新規プロジェクト作成
- 新しいプロジェクトを作成します。
@image html start_xcode_osx_newproject.png
- CocoaApplicationとして作成します。

2. 参照設定
- CrossFrameworkのプロジェクトファイルを参照するように設定します。
@image html start_xcode_osx_addproject.png
- 「~/Desktop/crossframework/Library/build/library/macosx/XLibrary.xproj」を作成したプロジェクトファイルにドラッグ＆ドロップしてください。
@image html start_xcode_osx_refproject.png
- 作成したプロジェクトのターゲットを「右クリック」「情報」を開き「ターゲット」タブの「直接依存関係」にXBaseを追加してください。
@image html start_xcode_osx_include.png
- 「ビルド」タブの「ヘッダ検索パス」に「~/Desktop/crossframework/Library/include」を追加してください。
@image html start_xcode_osx_preprocessor.png
- 「ビルド」タブの「プリプロセッサマクロ」に「XLIBRARY_DEBUG」を追加してください。
- （＊指定するプリプロセッサについて詳しく知りたい型は @ref AboutBuildVersion をご覧ください。）
@image html start_xcode_osx_addlib.png
- XLibraryのlibXBase.aをターゲットの「バイナリをライブラリにリンク」にドラッグ＆ドロップしてください。
- 以上で参照設定は終了です。
- （＊ここではXBaseしか参照設定しませんでしたが、AeG3dなど他のライブラリを参照するときも同様に設定してください。）

3. プログラム記述
- 試しにウィンドウを表示させるプログラムを記述します。
@image html start_xcode_osx_cpp.png
- main.m を main.cpp に名前変更します。
- デモのソースコード「~/Desktop/crossframework/Library/build/demo/src/XBase/display/Main.cpp」の内容をコピー＆ペーストします。
@image html start_xcode_osx_run.png
- ビルドして実行するとウィンドウが表示されます。


以上でチュートリアルは終了です。お疲れ様でした。 @n
なお、このプログラムはMacOSX以外にもWindows、iOSで動作します。@n
@n
その他のプログラムを書く場合は @ref DemoList のソースコードを参考にしてください。@n

*/
