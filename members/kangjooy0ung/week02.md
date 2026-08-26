# 📝 2주차 실습 정리 — <github-id>

## 1. 워크플로우 1바퀴 (필수)
- 작업한 것 (기능 개발 or 버그 수정): 맛집 DB 데이터 목록 화면에 로딩 중 상태(UI) 텍스트 추가
- 과정: 탐색 → 계획(Plan Mode) → 구현 → 검증(npm run dev로 로컬 테스트) → 커밋 → PR 완료
- 커밋 / PR 링크: https://github.com/db-matzip-project/matzip-frontend/pull/1
- 느낀 점: Plan Mode를 통해 AI가 무엇을 고칠지 미리 확인할 수 있어 안심이 되었고, 작업 단위가 작아 부담 없이 1사이클을 돌려볼 수 있었다.

## 2. CLAUDE.md
- `/init` 후 직접 손본 내용: 컴포넌트 작성 시 반드시 화살표 함수(Arrow Function)를 사용하고, 불필요한 console.log는 작성하지 않도록 규칙을 추가함.
- before/after — Claude의 답이 어떻게 달라졌나: "테스트용 빈 컴포넌트 코드 하나만 짜줘"라고 요청했을 때, 기존 방식(`export default function`)이 아닌 CLAUDE.md 규칙을 인식하여 `const TestComponent = () => {}` 형태의 화살표 함수로 코드를 정확히 작성해 주었다.

## 3. 커스텀 Slash Command + Hook
- 만든 커맨드 (`.claude/commands/ac.md`): `! git status` 결과를 바탕으로 변경사항을 확인하고 "chore: Claude 자동 커밋" 메시지로 자동 커밋을 수행하는 마크다운 기반 명령어 작성.
- 만든 Hook (`.claude/settings.json`): `PreToolUse` 훅을 사용해, Claude가 Bash 명령을 사용하기 전에 상태를 검사하도록 설정.
- 어떻게 연동했나: 채팅창에 `/ac`를 입력하니 Skill이 성공적으로 로드되며, 작성한 규칙대로 변경사항 스테이징 후 "chore: Claude 자동 커밋" 메시지와 함께 커밋이 정상적으로 완료되었다.

## 4. (도전) MCP / Plugin
- 연결한 MCP 서버 or 설치한 플러그인:
- 실제로 시켜본 작업 & 후기:

## 5. 회고
- 겪은 삽질: 처음에 터미널에서 `cd` 명령어로 프로젝트 경로(Desktop vs Documents)를 찾는 데 헤맸다. 또한 커스텀 커맨드를 쉘 스크립트(`.sh`)로 만들었다가 인식이 안 되는 오류(`Unknown command`)를 겪었는데, Claude Code 환경에 맞게 마크다운(`.md`) 파일로 재생성하고 터미널을 재시작하여  해결했다.
- 워크플로우가 어떻게 바뀌었나: AI에게 단순 코드 작성을 넘어서, 커밋 같은 반복 작업이나 프로젝트 컨벤션 유지까지 위임할 수 있어 작업 속도가 훨씬 빠르고 쾌적해졌다.
- 다음에도 또 쓸 세팅 1가지: `CLAUDE.md`를 활용한 프로젝트 컨벤션 강제 기능. 매번 프롬프트로 "화살표 함수로 해줘"라고 조건을 달지 않아도 되어 편리하다.