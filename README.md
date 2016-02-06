# 概要
[Siv3D](http://play-siv3d.hateblo.jp/) でさめがめを作りました。

# 新バージョンへの対応
[前プロジェクト](https://github.com/ZeitungM/SameGame)で使用していたバージョン(June2015v2)は、
新バージョン(January2016)のリリースの際に、プロジェクトの更新の対象外となったので、新しいプロジェクトを作成しました。

# 要改善点
* コードをもっと見やすく、わかりやすくする
* ブロックの設計の改良案を考える
* シーン管理を[公式サイトのサンプル](http://play-siv3d.hateblo.jp/entry/ref/scenemanager)を参考に改良する
* 深いネストをどうにかしたい
* placement new によるクラス配列をやめる(vectorに)
* 再帰を使わない塗りつぶし
* ブロックを消す処理とスコアを加算する処理を分離する
