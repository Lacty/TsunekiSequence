
#include <iostream>


template<class T> class Sequence {
public:
  // typedef�t���Ȃ���Scene���^�Ƃ��ĔF�������Ȃ�->err
  // <>�œn�������N���X�̒��̊֐��̃|�C���^���쐬
  typedef void(T::*Scene)();

  // �����œn�������N���X�̒��̊֐�として(now)�����s
  void exeAction(T* obj) {
    (obj->*now)();

    // now���̂��̂̎��s��err
    // 0 ���������荞�ފ֐��ɂ͕]�������܂���
    // now();
  }

  // �����Ŏ󂯎������֐���now�ɓ�����
  // SceneManager�̃R���X�g���N�^��title���w��
  void changeAction(Scene sequence = nullptr) {
    now = sequence;
  }

private:
  Scene now;
};

class SceneManager {
public:
  // �V���O���g��
  // SceneManager�����x������������
  static SceneManager& getInstance() {
    static SceneManager manager;
    return manager;
  }

  void title();

  // �V�[�������s�A�ڍs�Ȃǂ��Ǘ�����
  Sequence<SceneManager> sequence;

private:
  SceneManager() {
    // Pull Path�w�肵�Ȃ��Ɖ��z�֐��̃A�h���X�����낤�Ƃ���->err
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
