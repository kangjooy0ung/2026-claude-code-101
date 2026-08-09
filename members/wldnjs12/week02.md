# 📝 2주차 실습 정리 — wldnjs12

## 1. 워크플로우 1바퀴 (필수)
- 작업한 것 (기능 개발 or 버그 수정): domain.profile의 프로필 수정 API(PUT /api/v1/profiles/me)에 입력 검증(Bean Validation)이
  누락돼 있던 것을 추가. 탐색 단계에서 Claude가 "auth 패턴엔 @Valid가 있는데 profile엔 없다"는
  걸 스스로 발견해서 시작된 작업.
- 과정: 탐색 → 계획(Plan Mode) → 구현 → 검증(테스트) → 커밋 → PR
  · 탐색: domain.auth / domain.profile 코드 비교 → @Valid + 제약조건 누락 발견
  · 계획(Plan Mode): SignupRequest와 동일한 스타일로 ProfileUpdateRequest에 필드별 제약을
  넣기로. 단, docs/open-decisions.md의 A5(필수 입력 항목)가 '미결정'이라, 필수 지정은 하지
  않고 "값이 있을 때만 형식·길이 검증"으로 범위 확정.
  · 구현: ProfileUpdateRequest에 Bean Validation 어노테이션(@Size 등) 추가,
  ProfileController.updateProfile에 @Valid 추가.
  · 검증: DB 없이 도는 standalone MockMvc 테스트 4종 작성 → 4/4 통과
  (bio 500자 초과·mbti 형식 오류·tags 10개 초과 → 400, 정상 → 200).
- 커밋 / PR 링크: https://github.com/INHA-BE-Study/INHA-Service/pull/7
- 느낀 점: 계획부터 시작하니 범위가 명확해졌고, 특히 미결정 사항을 코드가 멋대로
  정하지 않게 막을 수 있었다. 테스트를 먼저 짜서 검증 없을 땐 통과하고, 추가하니 400 흐름을
  눈으로 확인하니 변화가 선명했다. 중간에 Spring Boot 4.0.6에서 @WebMvcTest가 별도 모듈로
  분리돼 컨텍스트 로딩이 계속 깨졌는데, DB·시큐리티 컨텍스트가 아예 필요 없는 standalone
  MockMvc로 방향을 틀어 해결했다 — 도구의 한계를 우회하는 판단도 워크플로우의 일부였다.

## 2. CLAUDE.md
- `/init` 후 직접 손본 내용: 이 프로젝트는 CLAUDE.md가 이미 잘 정비돼 있어 새로 /init 하거나 규칙을 추가할 필요는 없었다. 대신 "기존
  CLAUDE.md 규칙이 실제 작업에서 Claude의 행동을 어떻게 바꾸는가를 관찰했다

- before/after — Claude의 답이 어떻게 달라졌나:
  · 상황: 프로필 검증을 추가하려는데 open-decisions.md의 A5(프로필 필수 입력 항목)가 '미결정'.
  · before: 검증을 넣는 김에 mbti·loveStyle 등을
  임의로 @NotBlank 필수로 지정해버렸을 것이다
  · after: 미결정 항목은 임의로 구현하면 안 된다는 규칙 때문에
  Claude가 필수 항목을 스스로 정하지 않고 필수 처리를 어떻게 할까요?라고 나에게 되물었다.
  결과적으로 '전부 선택 입력 유지 + 형식 검증만'으로 안전하게 범위를 좁혔다.
 
## 3. 커스텀 Slash Command + Hook
- 만든 커맨드 (`.claude/commands/...`):
  · /commit — git status·diff를 자동으로 읽어와 Conventional Commits 형식으로 커밋 생성
  (.claude/commands/commit.md, allowed-tools: Bash(git:*))
  · /review — git diff HEAD를 넣어 커밋 전 셀프 리뷰(버그 가능성·CLAUDE.md 컨벤션 위반·
  테스트 누락·시크릿 노출을 심각도 순으로 지적) (.claude/commands/review.md)

- 만든 Hook (`.claude/settings.json`):
  Stop 훅 — Claude가 작업을 끝내고 멈출 때 macOS 알림 소리(afplay Glass.aiff) + 데스크톱
  알림(osascript)을 띄운다. 긴 빌드·테스트를 돌려두고 자리를 비워도 완료를 즉시 인지.

- 어떻게 연동했나:
  /review로 변경을 먼저 점검 → /commit으로 컨벤션 맞춰 커밋하는 흐름을 만들고, 그 사이
  파일 수정·빌드가 끝날 때마다 Stop 훅이 소리로 알려줘 "리뷰 → 커밋 → (긴 작업) → 알림"이
  끊기지 않게 했다.

## 4. (도전) MCP / Plugin
- 연결한 MCP 서버 or 설치한 플러그인: PostgreSQL MCP 서버(@modelcontextprotocol/server-postgres). 로컬 docker의 postgres
  (localhost:5433)에 연결. `claude mcp add postgres ...`로 프로젝트 스코프(~/.claude.json)에
  등록 → 세션 재시작 후 /mcp에서 "connected · 1 tool" 확인.
- 실제로 시켜본 작업 & 후기"현재 테이블/스키마를 보여주고 domain.match에 필요한데 빠진 걸 짚어줘"를 시킴 →
  Claude가 실제 DB를 읽어, match 도메인은 테이블·코드가 0부터 시작해야 하고 그 전에
  (a) User.last_login_at 추가 여부 (b) A3 활성 유저 N일 기준 (c) report.Block 최소 구현
  여부를 먼저 정해야 하드/소프트 필터를 짤 수 있다고 정리해줌.
  후기: 코드·마이그레이션을 안 열고도 "실제 DB 상태 + CLAUDE.md 규칙"을 함께 근거로
  설계 갭을 짚어준 게 인상적. 특히 CLAUDE.md §7 규칙대로 A1/A3 미결정 값을 임의로 정하지
  않고 "팀 확인 필요"로 남겨둔 점이, MCP가 규칙까지 지키며 동작함을 보여줬다.

## 5. 회고
- 겪은 삽질:
  Spring Boot 4.0.6에서 @WebMvcTest가 별도 모듈로 분리되고 시큐리티·OAuth 자동설정을 끌어와
  테스트 컨텍스트 로딩이 계속 실패. DB·시큐리티가 필요 없는 standalone MockMvc(컨트롤러 +
  GlobalExceptionHandler 직접 등록)로 바꿔 해결. 또 docker 데몬이 꺼져 있어 DB가 안 떠서
  MCP 연결이 막혔는데, Docker Desktop을 켜고 compose로 postgres를 올린 뒤 해결.

- 워크플로우가 어떻게 바뀌었나: "질문 → 바로 코드"에서 "탐색 → 계획(Plan Mode) → 테스트 먼저 → 구현 → 리뷰 → 커밋/PR"로.
  계획 단계에서 미결정 사항(A5)을 걸러 임의 구현을 막았고, 테스트를 먼저 짜 변화를 눈으로
  확인하는 습관이 생겼다.

- 다음에도 또 쓸 세팅 1가지 : Stop 훅은 앞으로 어떤 프로젝트를 하든 잘 쓸 것 같다. 긴 빌드·테스트를 돌려두고 다른 일 하다가 
  끝나는 즉시 알 수 있어 체감이 가장 컸다.