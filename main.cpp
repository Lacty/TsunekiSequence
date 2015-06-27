
#include <iostream>


template<class T> class Sequence {
public:
  // typedef付けないとSceneが型として認識されない->err
  // <>で渡されるクラスの中の関数のポインタを作成
  typedef void(T::*Scene)();

  // 引数で渡されるクラスの中の関数として(now)を実行
  void exeAction(T* obj) {
    (obj->*now)();
    
    // nowそのものの実行はerr
    // 0 引数を取り込む関数には評価されません
    // now();
  }

  // 引数で受け取った関数をnowに入れる 
  // SceneManagerのコンストラクタでtitleを指定
  void changeAction(Scene sequence = nullptr) {
    now = sequence;
  }

private:
  Scene now;
};

class SceneManager {
public:
  // シングルトン
  // SceneManagerを一度だけ生成する
  static SceneManager& getInstance() {
    static SceneManager manager;
    return manager;
  }

  void title();

  // シーンを実行、移行などを管理する
  Sequence<SceneManager> sequence;

private:
  SceneManager() {
    // Pull Path指定しないと仮想関数のアドレスを取ろうとする->err
    sequence.changeAction(&SceneManager::title);
  }
};

void SceneManager::title() {
  std::cout << "Title" << std::endl;
}


int main(){
  SceneManager::getInstance().sequence.exeAction(&SceneManager::getInstance());
  return 0;
}