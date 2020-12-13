<h2>컴파일 및 실행방법</h2>

아래 2가지 방법 중 하나를 선택하여 실행할 수 있습니다.<br>
**① visual studio <br>**
컴파일한 환경은 windows10, 64bit 운영체제입니다.<br>
C++ 언어 표준은 C++17 표준을 사용하였습니다.<br>
우선 git clone을 통해 프로젝트 repo를 가져옵니다.<br>
그 후 가져온 프로젝트 폴더에서 솔루션(sln)을 visual studio로 엽니다.<br>
그러면 헤더 파일과 소스 파일이 분리되어 있는 것을 확인할 수 있습니다.<br>
여기서 소스 파일에 있는 main.cpp에서 프로그램 실행을 통해 프로그램을 실행하면 프로그램이 실행됩니다.<br>
<br>
**② repl.it 기준으로 clang 이용<br>**
우선 헤더 파일들과 소스 파일들을 복사하고 붙여넣기 해줍니다.(저같은 경우에는 업로드 파일로가져오면 한글이 깨졌습니다.)<br>
이렇게 한글이 깨지지 않는 상태로 헤더와 소스 파일을 가져옵니다.<br>
그 후 repl.it을 기준으로 창에서 main.cpp 소스 파일을 제외하고<br>
clang++ -c BadakHand.cpp<br>
clang++ -c Board.cpp<br>
clang++ -c Card.cpp<br>
clang++ -c CardSet.cpp<br>
clang++ -c Dummy.cpp<br>
clang++ -c EndGameUtil.cpp<br>
clang++ -c Player.cpp<br>
이렇게 7개의 cpp 파일에 대해 수행하여 7개의 .o 파일을 만들어줍니다.<br>
그 후 clang++ main.cpp BadakHand.o Board.o Card.o CardSet.o Dummy.o EndGameUtil.o Player.o<br>
을 통해 링킹을 해서 실행 파일인 a.out을 만듭니다.<br>
그 후 ./a.out을 통해 실행해보면 고스톱 프로그램이 실행됩니다.<br>
<br>

<h2>실행 방법(게임 수행 방법)</h2>

우선 visual studio 상에서 헤더 파일들은 헤더 파일에 넣고 소스 파일들은 소스 파일들에 넣습니다.<br>
그 후 visual studio에서 소스파일 중 main.cpp에서 실행버튼을 눌러 실행하게 됩니다.<br>
그러면 플레이어의 이름을 입력받게 됩니다. 그러면 3인용 고스톱 게임이므로 이름을 3번 입력받게 됩니다.<br>
이름을 3번 입력한 후에는 순서를 정하기 위해 각 플레이어가 바닥 카드를 선택하게 됩니다.<br>
여기서 선택할 카드를 숫자로 입력하여 선택한 후 가장 큰 숫자(월)을 선택한 사람 순으로 게임이 진행됩니다.<br>
플레이어 차례가 되면 우선 패에서 어떤 카드를 낼지 입력받습니다.<br>
입력해서 카드를 내면 짝이 맞다면 바닥에서 선택할 수 있는 카드를 보여줍니다.<br>
그러면 짝이 맞는 카드를 보고 원하는 카드를 선택하면 됩니다.<br>
그 후 더미에서 카드를 뽑게 됩니다. 마찬가지로 짝을 만들 수 있으면 짝이 맞는 카드를 출력하고 맞는 카드를 선택해서 가져오면 됩니다.<br>
반대의 경우에는 카드를 내서 짝을 만들 수 없으면 바닥에 내려놓고 더미에서 카드를 뒤집어 짝을 만들 수 없는 경우에도 바닥에 내려 놓습니다.<br>
이 때 이 과정에서 뻑, 따닥, 쪽을 검사합니다. 만일 셋 중 해당하는 경우가 있으면 해당 내용에 맞게 수행하도록 합니다.<br>
여기서 피를 받아올 때 임의로 피를 받아옵니다. 이렇게 차례대로 플레이어가 돌아가며 게임을 진행하다 누군가 3점 이상이 나서 스탑을 하면 게임이 끝나게 됩니다.<br>
게임이 끝나면 바닥패로 난 점수에 고로 난 점수, 멍박, 광박, 피박, 고박을 따져서 최종 점수를 계산하게 됩니다.<br>
이 때 고박이면 고박 당한 사람을 알려줍니다. 그 후 진 사람들의 입장에서 계산된 승자의 최종 점수를 출력해주고 고스톱이 종료됩니다.<br>
만일 고를 선택하면 게임은 계속 진행되게 됩니다. 만일 마지막 턴까지 진행하고도(즉, 더미와 손패가 모두 소진된 경우) 결착이 나지 않는다면 나가리 판이라고 메세지를 출력합니다.<br>
