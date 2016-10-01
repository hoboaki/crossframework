/**

@page AboutBuildVersion ビルドバージョン
@section ビルドバージョン
・CrossFrameworkは4つのビルドバージョンを持ちます。@n
・アプリケーションは使用するビルドバージョンのプリプロセッサをコンパイル時に定義するようにしてください。@n
<table>
<tr><th>名前</th><th>プリプロセッサ</th><th>エラー処理</th><th>コンソール出力</th><th>最適化</th></tr>
<tr><td>debug</td><td>XLIBRARY_DEBUG</td><td>o</td><td>o</td><td>-</td></tr>
<tr><td>develop</td><td>XLIBRARY_DEVELOP</td><td>o</td><td>o</td><td>o</td></tr>
<tr><td>semifinal</td><td>XLIBRARY_SEMIFINAL</td><td>-</td><td>o</td><td>o</td></tr>
<tr><td>final</td><td>XLIBRARY_FINAL</td><td>-</td><td>-</td><td>o</td></tr>
</table>
・エラー処理が有効なバージョンではASSERTが有効になり、エラー時に XBase::RuntimeError::OnError() が呼ばれます。@n
・エラー処理が無効なバージョンのほうがCPU・メモリパフォーマンスは優れています。@n
・コンソール出力が有効なバージョンでは XBASE_COUT() などのマクロで指定された文字列がコンソールに出力されます。@n
・コンソール出力が無効なバージョンのほうがCPU・メモリパフォーマンスは優れています。@n
・最適化が有効なバージョンではコンパイル時にコード最適化が実行されます。@n

@n

*/
