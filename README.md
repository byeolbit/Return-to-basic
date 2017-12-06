# Return-to-basic
Basic CS knowledges for interview

- Data structure
- Algorithm
- OS

## Data Structure

### Array

인덱스로 찾아지는 값들의 집합.

N개의 데이터가 있다면 메모리 공간은 N*자료형 만큼 할당된다.

**고정배열**
메모리의 스택 영역에 고정된 공간만큼 할당되어 크기의 변경이 불가능.

**동적배열**
메모리의 힙 영역에 할당되어 크기의 변경이 가능.
새로운 값이 추가될 때 마다 메모리의 할당 재할당이 이루어지는데 빈번하게 일어나면 손해이기 때문에 추가할 때 마다 여유분을 두고 추가된다.

### Stack

하노이의 탑과 같이 위로 쌓이는 자료들의 집합.
Last In First Out


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

Key와 Value를 가지는 Dictionary타입의 자료형
index를 key를 해싱하여 나온 값으로 배치

index는 key와 array의 size를 



### Queue

First In First Out
큐에 추가되는 아이템은 처음 들어온 순서대로 나가게된다.

- Enqueue : 큐의 제일 마지막에 아이템을 추가
- Dequeue : 큐의 제일 처음 아이템을 제거
- Peek : 큐의 제일 처음 아이템을 골라냄(제거하지는 않음)

**Priority Queue**

자체적인 기준에 의한 우선순위를 비교하여 우선순위가 높은 아이템이 큐의 제일 앞으로 들어오게 된다.

Heap을 이용해서 구현 가능.

**Double Ended Queue**

큐의 처음과 끝 동시에 삽입과 제거가 가능한 형태의 큐이다.


### Graph



### Tree

Root를 가지며 자식 노드들로 이루어지는 데이터들의 집합.



**Binary Search Tree**



#### Binary Search Tree

#### Heap





## Algorithm
