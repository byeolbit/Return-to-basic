# Return-to-basic
Basic CS knowledges for interview

- Data structure
- Algorithm
- OS

## Data Structure

### Array

인덱스로 찾아지는 값들의 집합.

N개의 데이터가 있다면 메모리 공간은 N*자료형 만큼 할당된다.

고정배열

메모리의 스택 영역에 고정된 공간만큼 할당되어 크기의 변경이 불가능.

동적배열

메모리의 힙 영역에 할당되어 크기의 변경이 가능.

새로운 값이 추가될 때 마다 메모리의 할당 재할당이 이루어지는데 빈번하게 일어나면 손해이기 때문에 추가할 때 마다 여유분을 두고 추가된다.

### Stack

하노이의 탑과 같이 위로 쌓이는 자료들의 집합.

Last in First out


### Linked List

하나의 노드가 다른 노드를 참조하는 방식으로 체이닝되어있는 노드들의 집합.
노드를 단방향으로 참조할 수 도 있고, 양방향으로 참조할 수 도 있다.

n개의 노드로 구성된 Linked List에서
- 노드를 삽입하는데 걸리는 시간 복잡도는 O(1)
- 노드를 찾는데 걸리는 시간 복잡도는 O(n)
- 특정한 노드를 삭제하는데 걸리는 시간 복잡도도 O(n)

단방향 링크드 리스트의 구성
- 각 노드에 참조는 하나 뿐
- 제일 첫 노드가 Head
- null을 가리키는 마지막 노드가 Tail

양방향 링크드 리스트의 구성
- 각 노드는 앞 노드와 뒤 노드를 참조하는 두 개의 참조로 구성
- 앞 노드를 가리키는 참조가 null인 노드가 Head
- 다음 노드를 가리키는 참조가 null인 노드가 Tail 

### Hash Table



### Queue

### Graph

### Tree

#### Binary Search Tree

#### Heap



## Algorithm
