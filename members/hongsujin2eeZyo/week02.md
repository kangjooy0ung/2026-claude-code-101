# Claude Code 2주차 실습

## ✅ 체크리스트

- [x] 실제 코드베이스에서 기능 개발 or 버그 수정 1건
- [x] Claude Code로 커밋 & PR 생성
- [x] `CLAUDE.md` 작성해보기
- [x] Hook 또는 Slash Command 1개 만들어보기
- [x] MCP 서버 개념 이해 (가능하면 1개 연결)
- [x] `members/<github-id>/week02.md`에 정리

## 1. 워크플로우 1바퀴

1.  탐색
    - CLAUDE.md 작성을 위해 소스 전체(App.js, useFetch.ts, 컴포넌트 6개, data.json, package.json) 읽고 아키텍처 파악
    - 프로젝트 구조 분석: CRA 기반 단어장 SPA, 라우팅 구조, 컴포넌트별 fetch 패턴, days/words 데이터 모델 정리

2.  문제 진단 및 계획
    - 코드 리뷰로 발견한 문제 정리:
    - 🔴 로딩/빈 목록 구분 안 됨(무한 "Loading...")
    - 🔴 id 타입 불일치, fetch 에러 처리 없음
    - 🟡 API URL 하드코딩, json-server 백엔드 자체가 리포에 없음
    - 🟢 테스트 없음, tsconfig.json 없음 등
    - 사용자와 우선순위 논의 → **"useFetch 개선 + json-server 셋업"**이 가장 효과적이라는 데 합의
    - Plan 서브에이전트에게 상세 설계 위임 → useFetch<T>가 {data, isLoading, error}를 반환하는 구조, 4개 컴포넌트 변경 방식, json-server devDependency 추가 방식(정확한 버전 고정 근거 포함)을 구체적 코드로 설계받음

3.  구현
    - src/hooks/useFetch.ts: 제네릭 useFetch<T> 훅으로 재작성 — {data, isLoading, error} 반환, url 변경 시 상태 리셋, res.ok 체크 + 네트워크 에러 처리, stale 응답 방지용 isCurrent 가드
    - DayList.tsx, Day.tsx, CreateWord.tsx, CreateDay.tsx: 새 훅 반환값에 맞춰 로딩/에러/빈 목록을 각각 다른 문구("불러오는 중...", "에러가 발생했습니다: ...", "Day가 없습니다"/"단어가 없습니다")로 렌더링하도록 수정 (Word.tsx는 변경 불필요)
    - package.json: json-server(1.0.0-beta.15, 버전 고정) devDependency 추가 + "server" 스크립트 추가
    - npm install --legacy-peer-deps로 설치 (기존에 있던 typescript peer 충돌은 이번 작업과 무관한 리포 기존 이슈라 우회 처리)

4.  검증 (실제 브라우저 기준)
    - 3001 json-server — /days, /words?day=1 응답 정상 확인
    - 3002 CRA dev 서버 — 처음엔 번들이 stale하다고 오판했으나(한글이 유니코드 이스케이프로 인코딩돼 grep이 실패한 것뿐), 실제로는 정상 반영된 상태였음을 재확인
    - Day 6(단어 없는 Day)에서 "단어가 없습니다"가 정상적으로 뜨는 것을 사용자가 직접 확인 → 로딩/빈 목록 구분 버그 해결 확인
    - 3001 서버를 잠깐 내렸다가 사용자가 브라우저에서 "에러가 발생했습니다" 문구가 뜨는 것을 직접 확인 → 다시 서버 재시작으로 복구 확인

    세 가지 상태(로딩 / 빈 목록 / 에러) 모두 실제 화면에서 검증 완료된 상태입니다.

5.  커밋
    https://github.com/hongsujin2eeZyo/claude-project/pull/1

## 2. CLAUDE.md

> 정렬/진행률 기능 개선해줘

### Before (CLAUDE.md 적용 전)

- 수정 파일: Day.tsx, Word.tsx, index.css
- Word.tsx의 상태를 제거하고 Day.tsx에서 상태 관리하도록 구조 변경
- soft-delete(id=0) 방식을 제거하고 filter 방식으로 삭제 처리
- 체크박스 변경 시 진행률/정렬이 실시간 반영됨

### CLAUDE.md 규칙 추가

- 기존 코드 구조를 유지하고, 불필요한 리팩터링을 하지 않는다.
- 명시적으로 요청하지 않은 경우 컴포넌트 간 상태 관리 구조를 변경하지 않는다.
- 기존에 사용 중인 데이터 패칭 방식(fetch, useFetch)을 유지한다.
- 삭제 기능은 기존 soft deletion 방식(id=0)을 유지한다.
- 작업 완료 후 npm run build를 실행하여 빌드 오류를 확인한다.

### After (CLAUDE.md 적용 후)

- 수정 파일: Day.tsx, index.css
- Word.tsx 수정 없이 기존 상태 관리 구조 유지
- soft-delete(id=0) 방식 유지
- 진행률과 정렬은 최초 fetch 기준으로 동작
- npm run build 정상 통과

### 결과

CLAUDE.md 적용 후 기존 구조를 유지하는 방향으로 변경되었지만,
상태 공유가 필요한 기능에서는 실시간 반영이 어려워지는 트레이드오프가 발생함.

### 느낀점

이번 테스트에서는 CLAUDE.md의 효과를 확인하기 위해 일부러 강한 제약 조건을 추가해보았고, 그 결과 기존 구조를 보호하는 데는 효과적이었지만 기능 개선 과정에서 필요한 리팩터링까지 제한하는 상황이 발생했습니다.
이를 통해 CLAUDE.md는 단순히 규칙을 많이 작성하는 것이 중요한 것이 아니라, 프로젝트 상황에 맞는 적절한 기준과 우선순위를 설정하는 것이 중요하다는 것을 알게 되었습니다. 실제 프로젝트에서는 불필요한 변경은 방지하면서도 필요한 개선은 허용할 수 있도록 더 균형 있게 작성해 활용해야겠다고 느꼈다

# 3. /commit Command + PreToolUse Hook

## /commit Command

- 변경사항 확인
- 커밋 메시지 작성
- git commit 실행

## PreToolUse Hook

- git commit 실행 전에 자동 실행
- eslint --fix를 통한 코드 정리
- 변경 파일 자동 staging
- 테스트 실패 시 커밋 차단

```json
"hooks": {
    "PreToolUse": [
      {
        "matcher": "Bash",
        "hooks": [
          {
            "type": "command",
            "command": "bash .claude/hooks/pre-commit-check.sh",
            "if": "Bash(git commit *)",
            "timeout": 120,
            "statusMessage": "커밋 전 eslint --fix 및 테스트 실행 중..."
          }
        ]
      }
    ]}
```

## 결과

기존에는 개발자가 직접 lint와 테스트를 실행한 뒤 커밋해야 했지만,
Hook을 활용하면서 커밋 직전에 자동으로 품질 검사를 수행할 수 있게 되었다.
이를 통해 실수로 테스트되지 않은 코드를 커밋하는 상황을 방지할수있게되었다.

# 4. MCP 서버 - playwright

claude mcp add playwright npx @playwright/mcp@latest

Playwright MCP 서버를 추가하여 Claude Code가 브라우저를 직접 제어할 수 있도록 구성했다.

❯ http://localhost:3002/day/1 페이지를 열고
단어 체크박스가 정상 작동하는지 테스트해줘

![alt text](<./img/w2/스크린샷 2026-07-24 오후 11.48.53.png>)

## 결과

Claude가 Playwright MCP를 통해 브라우저를 실행하고,

- 페이지 접속
- 단어 목록 확인
- 체크박스 클릭
- 화면 변화 확인
- 디버깅

과정을 직접 수행했다.

기존에는 빌드 성공 여부만 확인할 수 있었지만, MCP를 활용하면서 실제 브라우저 환경에서 사용자 행동 기반 테스트가 가능하다는점이 정말 신선하다!!!

---

# 겪은 삽질

## Slash Command 반영 문제

커스텀 Slash Command를 생성한 후 원하는 동작이 나오지 않아 원인을 확인했다.

확인 결과 입력한 명령어가 `/commit`이 아닌 `/doctor`로 인식되고 있었으며,
Claude Code 재시작을 하지 않아 새로 추가한 커맨드가 정상적으로 반영되지 않은 상태였다.

해결:

- Claude Code 재시작
- 커맨드 목록 확인
- 기존 커맨드와 중복되지 않는 이름 사용

설정 변경 후에는 반드시 재시작 과정이 필요하다는 점을 경험했다.

---

# 워크플로우가 어떻게 바뀌었나

## 기존

기능 구현
직접 테스트
수동 검증
커밋
코드 분석
테스트
커밋

> 반복 작업을 직접 수행했다.

## 변경 후

CLAUDE.md로 프로젝트 규칙 공유
Claude Code로 분석 및 구현
Hook으로 자동 검사
Playwright MCP로 실제 브라우저 검증
/commit으로 일관된 커밋

이번 실습을 통해 Claude Code를 단순히 코드를 생성하는 도구가 아니라,
프로젝트 분석부터 검증, 커밋 과정까지 함께하는 개발 도구로 활용할 수 있다는 점을 경험했다.

---

# 다음에 또 쓸 세팅

## 1. Stop Hook - 작업 완료 알림

Claude가 긴 작업을 수행한 뒤 답변을 기다리는 상황을 놓치는 경우가 있어,
Stop Hook을 활용해 작업 종료 시 알림음을 설정해두면 유용할 것 같다.

## 2. /commit Command 활용

이번에 만든 `/commit` Command는 커밋 메시지 규칙을 명확하게 작성할수록 효과가 높다는 것을 느꼈다.

앞으로 프로젝트에서는:

- Conventional Commit 적용
- 제목/본문 작성 규칙 지정
- 변경 내용 기반 커밋 메시지 생성

등을 미리 정의해두고 일관된 커밋 기록을 남기는 용도로 활용할 예정이다.

## 3. Playwright MCP 활용

Playwright MCP를 처음 사용했을 때 Claude가 직접 브라우저를 실행하고,
화면 위에서 마우스를 움직이며 실제 사용자처럼 동작하는 모습이 인상적이었다.

단순히 코드를 분석하는 것을 넘어,
페이지 이동, 동작 확인, 오류 원인 추적까지 직접 수행하는 모습을 보면서 프론트엔드 개발에서 큰 활용 가능성을 느꼈다.
