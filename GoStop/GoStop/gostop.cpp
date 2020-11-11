#include <iostream>

// ȭ���� Ŭ����
class Card {
 public:
  explicit Card() { name_[0] = 0; }

  // ������ : ī�� �̸��� ���ڷ� �޾� ��� ���� name_�� �����մϴ�.
  explicit Card(const char* name) {
    strcpy_s(name_, 4, name);
  }

  // ī���� ���� �̸��� ù ��° �����Դϴ�.
  // 10~12���� ���ܷ� ���� K, L, M�� ��Ÿ���ϴ�.
  int GetMonthOfCard() const {
    if (isdigit(name_[0])) return name_[0] - '0';
    if (name_[0] == 'K') return 10;
    if (name_[0] == 'L') return 11;
    return 12;
  }

  // ī���� ������ ���ڷ� ��ȯ�մϴ�.
  // ũ�� ��, ��(����), ��(��), ���� 4������ ������,
  // �ߺ��� Ư���� �ִ� ���(ex. �������� ����, �������� ���� ��) Ȥ��
  // ȫ��,û��,�ʴ�,��,������ ������ �ʿ��� ���(������� ��)����
  // �ش� �Լ����� ī���� ���� Ȯ���Ͽ� �����ϸ� �� �� �����ϴ�.
  // ex) ����&�������� Ȯ�� ->
  // if(CardSet[3].GetTypeOfCard() == 1 && CardSet[3].GetMonthOfCard() == 2 or 4 or 8)
  int GetTypeOfCard() const {
    // 
    if (strcmp(&name_[1], "��") == 0) return 0;
    if (strcmp(&name_[1], "��") == 0) return 1;
    if (strcmp(&name_[1], "��") == 0) return 2;
    return 3;
  }

  // ī�� �̸��� ��ȯ�ϴ� �Լ�
  char* GetName() { return name_;  }

  // ���� ī��� �ٸ� ī�尡 ������ ���ϴ� �Լ�(== ������ overloading)
  bool operator==(const Card& other) { 
    if (strcmp(name_, other.name_) == 0)
      return true;
    else
      return false;
  }

  // *** �Ǵٸ� �� �Լ��� �ʿ��ϴٸ� �߰��� �ּ��� ***

 private:
  char name_[4];
};

int main() { 
  Card CardSet[2] = {Card("1��"), Card("1��")};
  std::cout << CardSet[0].GetName() << std::endl;
  std::cout << CardSet[1].GetName() << std::endl;
  if (CardSet[0] == CardSet[1]) 
    std::cout << "same" << std::endl;
  else
    std::cout << "different" << std::endl;

  return 0;
}