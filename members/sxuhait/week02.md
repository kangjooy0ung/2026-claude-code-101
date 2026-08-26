# 📝 2주차 실습 정리 — <github-id>

## 1. 워크플로우 1바퀴 (필수)
- 작업한 것 (기능 개발 or 버그 수정):
     문자열 처리 실습 파일 생성 및 깃허브 연동 (PR 생성)
- 과정: 탐색 → 계획(Plan Mode) → 구현 → 검증(테스트) → 커밋 → PR
    계획: 클로드가 제시한 '문자열 처리 실습 파일 생성 계획'을 확인하고 1. Yes, and use auto mode를 선택하여 승인함.

    구현: 승인 직후 클로드가 스스로 JavaScript 실습 파일을 생성함.

    커밋/PR: GitHub CLI 연동 중 gh 권한 인증 에러가 발생했으나, 터미널에 뜬 일회용 디바이스 코드(8자리)를 발급받아 웹 브라우저에서 성공적으로 권한을 부여한 뒤 커밋과 PR 생성을 마저 위임함.
- 커밋 / PR 링크:
    커밋: https://github.com/sxuhait/2026-claude-code-101/commit/32299f89f4a558141862a0fca68e059e569c7ba3
    PR: https://github.com/LandvibeDev/2026-claude-code-101/pull/12
- 느낀 점: 코드를 짜기 전에 Plan Mode로 설계도를 미리 확인하고 승인하니 훨씬 안정적이었습니다. 특히 깃허브 연동 과정에서 권한 문제로 막혔을 때 당황하지 않고 클로드에게 상황을 넘겼더니, 일회용 코드를 통한 기기 인증 해결책까지 가이드해 주어서 AI에게 '디버깅을 위임'한다는 게 어떤 느낌인지 알게 되었습니다.

## 2. CLAUDE.md
- `/init` 후 직접 손본 내용:
    기존 설정(ex. .env 차단 훅)이 자동으로 문서화된 것에 더해, 하단에 커스텀 규칙 3가지를 명시함.

    빌드/실행: JavaScript 환경에 맞춘 실행 명령어 명시.

    컨벤션: 모든 주석은 '한국어 존댓말'로 필수 작성, 커밋 메시지 말머리에 [실습완료] 의무화.

    금지사항: main 브랜치 직접 푸시 엄격히 금지.
- before/after — Claude의 답이 어떻게 달라졌나:
    적용 전에는 일반적인 영어 주석과 feat: add ... 형태의 영어 커밋 메시지를 뱉어냄

    적용 후에는 지시한 대로 코드 내에 정확하게 한국어 존댓말 주석을 달고, 추천 커밋 메시지 앞에도 [실습완료] 말머리를 빼놓지 않고 붙이는 것을 확인함. 프로젝트 팀의 컨벤션을 AI에게 아주 쉽게 강제할 수 있음을 체감함.

## 3. 커스텀 Slash Command + Hook
- 만든 커맨드 (`.claude/commands/js-commit.md`):
    /js-commit 명령어 등록. 파일 상태와 변경 내용을 읽은 뒤, JavaScript 코드 변경사항에 대한 커밋 메시지를 [실습완료] 말머리와 함께 제안하고 커밋을 자동 실행하도록 지시함.
- 만든 Hook (`.claude/settings.json`):
    기존 윈도우(PowerShell) 환경의 .env 파일 보호 훅(PreToolUse) 아래에 새로운 조건을 병합함. Bash 툴로 git commit을 시도할 때, .js 파일 내에 console.log가 남아있는지 우선 검사하도록 훅을 세팅함.
- 어떻게 연동했나:
    루트 경로에 test.js 파일을 만들고 의도적으로 console.log 코드를 작성함.

    터미널에 /js-commit 명령어를 입력해 커밋을 위임하자 훅이 이를 중간에 가로챔.

    파일 내에 console.log가 남아있는 것이 발각되어, "🚫 JS 파일에 console.log가 남아있어 커밋을 차단합니다!"라는 에러가 발생하고 exit 2가 실행되며 커밋 도구가 완벽히 강제 차단됨을 테스트로 증명함.

## 4. (도전) MCP / Plugin
- 연결한 MCP 서버 or 설치한 플러그인:
    `claude mcp add`로 sqlite MCP 서버(`mcp-server-sqlite`)를 연결함.
- 실제로 시켜본 작업 & 후기:
    처음엔 `npx @modelcontextprotocol/server-sqlite test.db`로 등록했지만 `claude mcp list`에서 연결 실패로 나옴. 원인을 파고 보니 해당 npm 패키지 자체가 존재하지 않는 것(404)이었고, 공식 SQLite MCP 서버는 npm이 아니라 Python 패키지(`mcp-server-sqlite`)로 배포되어 `uvx`로 실행해야 한다는 걸 알게 됨.

    `uv`(uvx)를 새로 설치한 뒤 `uvx mcp-server-sqlite --db-path test.db`로 서버 설정을 다시 등록하니 `claude mcp list`에서 연결 성공(✔)으로 확인됨.

    MCP 서버 이름만 보고 바로 되는 게 아니라, 패키지 배포 방식(npm vs Python/uv)에 따라 실행 명령어 자체가 달라진다는 걸 직접 에러를 겪으며 체감함.

    이후 새 세션에서 실제로 "test.db에 users 테이블 만들고 가상 데이터 넣고 조회해줘"라고 요청함. 클로드가 `mcp__sqlite__create_table`(id, name, role 컬럼), `mcp__sqlite__write_query`(가상 유저 2건 INSERT), `mcp__sqlite__read_query`(SELECT) 툴을 순서대로 호출해 결과를 표로 정리해 보여줌. MCP 툴이 등록만 되어 있으면 클로드가 별도 설명 없이도 DB CRUD를 알아서 분해해 수행한다는 걸 확인함.

    다만 실습 중 만들어진 `test.db`는 저장소에 커밋할 필요가 없는 로컬 산출물이라, `.gitignore`에 `*.db` 규칙을 추가해 실수로 커밋되지 않도록 조치함.

## 5. 회고
- 겪은 삽질:
    .claude/settings.json 파일 위치를 헷갈려 commands 폴더 하위에 잘못 만들 뻔함. 훅(Hook)이 프로젝트 전체에 제대로 동작하려면 반드시 루트의 .claude 직속 파일에 설정해야 한다는 것을 깨달음.

    윈도우(PowerShell) 환경으로 세팅된 기존 훅에 맥/리눅스용(Bash) 훅을 무작정 이어 붙이려다 JSON 문법 에러를 겪을 뻔함. 내 운영체제 환경에 맞는 셸(shell) 스크립트 병합이 무척 중요하다는 걸 체감함.
- 워크플로우가 어떻게 바뀌었나:
    이전에는 클로드에게 "커밋할 때 console.log 지웠는지 확인해 줘"라고 매번 프롬프트로 '부탁'했다면, 이제는 Hook을 통해 특정 이벤트 시점에 무조건 스스로 검사하도록 '강제'할 수 있게 됨.

    CLAUDE.md에 주석 규칙이나 커밋 말머리 규칙을 단 한 번만 세팅해 두니, 매번 지시사항을 길게 타이핑할 필요가 없어짐. 온전히 코드 로직 구현과 문제 해결에만 집중할 수 있게 되어 전체적인 작업 속도와 피로도가 개선됨.
- 다음에도 또 쓸 세팅 1가지:
    Slash Command + 커밋 전 위험 요소 차단 Hook 조합. 본격적으로 백엔드 서버를 개발하거나 실전 프로젝트를 진행할 때, 민감한 키값이나 디버깅용 로그(console.log), 미완성 코드(TODO)가 실수로 깃허브에 올라가는 걸 막아주는 이 파이프라인을 필수 안전장치로 계속 가져갈 계획임.