# 📝 3주차 실습 정리 — InSooBeen

📅 **07.20(월) ~ 07.26(일) 과제 주차** — 실제 착수는 07.26부터. Part 2. 실전 프로젝트 · 기획 & 착수

## 프로젝트: Kinly — 가족 건강 동반자

> 📎 기획서 전체: [Notion](https://cookie-moonstone-7ce.notion.site/369a44f2e1e3807282cbc0b6c657396e)

떨어져 사는 부모님을 챙기는 20~40대 자녀를 위한, **평소엔 안부 확인 앱·위기엔 비상 정보 금고**로 작동하는 가족 단위 건강 관리 서비스. 핵심 3기능(비상 정보 금고 / 안전 체크인 / 컨디션 추세)의 6주 계획 중 3주차는 **①비상 정보 금고**에 해당.

저장소는 실제 의료·비상 정보를 다루는 프로젝트라 **개인 private 레포**(`InSooBeen/kinly`)로 운영 중입니다. 코드 열람이 필요하시면 별도로 초대해 드릴 수 있고, 아래 각 일차 항목엔 **그날의 결정·트러블슈팅을 자세히 기록한 Notion 페이지**를 링크했습니다.

## ✅ 체크리스트

- [x] 프로젝트 주제 확정 — 가족 건강 동반자(Kinly)
- [x] 요구사항/기능 목록 문서화 — ADR 14건 (`docs/decisions/`)
- [x] 프로젝트 레포 셋업 — 모노레포(`server` Spring Boot + `app` Expo), Flyway 마이그레이션 9테이블
- [x] 프로젝트용 `CLAUDE.md` 작성
- [x] 첫 커밋 & 개발 착수 — 가족 그룹 / 구성원 프로필 / 비상 정보 금고 API까지 구현·테스트 완료
- [x] 클라이언트 화면 1차 완주 — 로그인 → 그룹 목록 → 생성/합류 → 멤버·초대 코드까지 5화면 연결
- [x] 실기기 검증 결과를 반영해 **클라이언트 플랫폼 결정 재검토** — Expo(네이티브) → 반응형 웹앱 전환 설계·구현 계획 확정
- [x] 웹 전환 구현 계획(11개 태스크) SDD 실행 완주 — 로그인부터 그룹 생성/합류/멤버/초대까지 전 화면 웹으로 이관, `app/`(Expo) 완전 삭제
- [x] 초대 링크 전환 + 관점별 호칭 설계·구현(Task 1~6) — 6자리 코드 대신 그룹별 유니크 링크로 전환, ADR 0007 정정 근거로 관점별 호칭 스키마 신설(ADR 0020·0021)

## 일별 진행 상황

### 1일차 · 2026-07-26

- 기술 스택 전체 확정(Android 네이티브 + Expo, Spring Boot 4.1 + PostgreSQL, AWS Lightsail 등) — 처음엔 웹 PWA를 검토했으나 **"데모냐 실사용이냐"**를 다시 따져 네이티브 앱으로 전환
- 코어 도메인 설계 — 계정(User)과 사람(Person) 분리, 비상정보는 그룹이 아닌 **Person에 귀속**시켜 다중 가족 그룹 중복 문제 해결
- `kinly` 모노레포 생성, ADR 11건 + `V1__init.sql`(9테이블) 작성
- WSL 개발 환경 구축, `./gradlew compileJava` **BUILD SUCCESSFUL**

📎 상세: [Notion — 3주차 1일차](https://cookie-moonstone-7ce.notion.site/3-1-2026-07-26-3aaa44f2e1e3817b8242e94ce1997be7?source=copy_link)

### 2일차 · 2026-07-27

- Flyway 마이그레이션 실행, 필드 암호화 계층(`AES-256-GCM`) 구현 — 단위 테스트 8건 통과
- Expo 앱 스캐폴딩, **GitHub private 레포 생성 + 첫 푸시**, 브랜치 전략(`main` 단독) 확정
- 카카오 로그인 리다이렉트 후보가 전부 막혀(커스텀 스킴·포트 제한·Expo 인증 프록시 폐지) **서버 콜백 방식**으로 인증 설계 전환
- 가족 그룹 API → 구성원 프로필 API → 비상 정보 금고 API를 세션 10회에 걸쳐 순차 설계·구현
- 전체 테스트 **47건 통과**로 마감

📎 상세: [Notion — 3주차 2일차](https://cookie-moonstone-7ce.notion.site/3-2-2026-07-27-3aaa44f2e1e3811db307fc4762f3f4d5?source=copy_link)

### 3일차 · 2026-07-28

- worklog·HANDOFF 날짜 체계를 실제 달력 기준으로 정합화
- 비상 정보 금고 API 커밋(`b819563`)
- **우선순위 재조정** — "핵심 기능부터"라는 피드백에 따라 PIN·감사로그 등 부가 보안 계층 대신 **앱 화면 구현**을 다음 착수 대상으로 결정
- `superpowers:brainstorming` 스킬로 앱 화면(로그인 → 그룹 생성/합류) 설계 스펙 5개 섹션 전부 승인받아 완료·커밋(`a61d37a`)
- `superpowers:writing-plans` 스킬로 구현 계획(Task 1~10) 작성 — 서버 소스 재확인 + Expo Router v57 공식 문서·타입 선언 직접 검증(스펙의 `<Redirect>`를 v57 권장 패턴인 `<Stack.Protected guard>`로 교체 결정 포함), 실행 방식은 **Subagent-Driven** 선택 → 계획 문서 커밋(`563081b`)
- `superpowers:subagent-driven-development`로 SDD 착수 — Task 1(API 클라이언트 `client.ts` + Jest 인프라) 구현·리뷰·커밋(`05f384f`), Task 2(`auth.ts`/`groups.ts` 엔드포인트 함수) 구현(스테이징까지)

📎 상세: [Notion — 3주차 3일차](https://cookie-moonstone-7ce.notion.site/3-3-2026-07-28-3aba44f2e1e381c78e35de1f3c201f30?source=copy_link)

### 4일차 · 2026-07-30

- 백엔드 전용 세션 — PostgreSQL 기동 후 서버 전체 테스트 재검증(**BUILD SUCCESSFUL**, 실패 0건), 이력 조회·되돌리기(revert) 엔드포인트 + ADR 0015 커밋
- 검증이 끝난 격리 브랜치 2개를 ADR 0014대로 `main`에 되돌림 — PR #2 `feat/emergency-vault-core`(19파일 1,071줄), PR #4 `feat/emergency-vault-history`(8파일 218줄) 병합
- **SDD Task 2~8을 하루에 완주** — auth/groups API 함수(`f537181`) → `expo-secure-store` 기반 AuthContext(`fb8f710`) → 공용 컴포넌트 4종(`4a6cc2c`) → `<Stack.Protected>` 인증 배선 + 로그인 화면(`27b0e92`) → 그룹 목록(`b073331`)·생성(`7fd88fa`)·합류(`1bf4efc`)
- 리뷰 과정에서 `npx expo install`이 만든 `app.json` 변경이 스테이징에서 빠진 건, Expo Router 라우트 타입이 갱신되지 않은 건(WSL2 `/mnt/d` 파일 감시 문제로 추정)을 잡음. **리뷰어 리포트의 `tsc` 결과 서술이 부정확했던 건은 직접 타입체크를 돌려 확인** — 서브에이전트 리포트를 그대로 믿지 않는 원칙이 실제로 값을 함

📎 상세: [Notion — 3주차 4일차](https://cookie-moonstone-7ce.notion.site/3-4-2026-07-30-3ada44f2e1e38193bd56dfb38d2d9594?source=copy_link)

### 5일차 · 2026-07-31

- **SDD Task 9**(그룹 멤버 화면 + 초대 코드 발급 인라인, `9c95481`)로 앱 화면 코드 태스크 1~9 완주 — 로그인부터 멤버·초대 코드까지 연결
- Task 10(수동 E2E)에서 실기기 확인을 수행 — 화면 코드는 계획대로 됐는데 **실행을 위한 마찰**이 계속 나왔다: Expo Go가 지원하는 SDK에 맞추느라 SDK 57 → 54 전면 다운그레이드, 안전 영역이 안 잡혀 `SafeAreaProvider` 추가, 여기에 전날의 WSL2 파일 감시 문제까지
- 그래서 **클라이언트 플랫폼 결정(ADR 0001) 자체를 재검토**했다. ADR 0001은 네이티브의 단점을 지울 때 "가족 전원이 Android"라는 전제를 썼으면서, 웹의 단점(푸시)을 판단할 땐 그 전제를 적용하지 않았다 — **전제의 비대칭 적용**. 같은 전제를 웹에 적용하면 Android Chrome의 Web Push는 네이티브 FCM과 실질적으로 같다. "상황이 바뀌었다"가 아니라 **"원래 논증의 어디가 틀렸는지"**로 적었다
- `superpowers:brainstorming`으로 전환 설계 spec 작성·커밋(`bcf03e9`) — Vite + React + Tailwind, Web Push(VAPID), 기존 ADR은 지우지 않고 supersede, `app/` 삭제 후 `web/` 신규
- 처음에 "CORS 설정이 없으니 서버 변경이 필요하다"고 말했다가 **정정**했다. 개발은 Vite dev 프록시, 운영은 nginx 동일 오리진 서빙이면 양쪽 다 same-origin이라 **`server/` 변경은 0건**이다
- `superpowers:writing-plans`로 구현 계획 11개 태스크 작성·커밋(`7f72118`). 계획 자체 리뷰에서 **통과해도 의미 없는 테스트**를 발견 — 모듈 전역 토큰을 `afterEach`에서 초기화하지 않아 세션 복원 로직이 깨져도 이전 테스트에서 새어 나온 토큰으로 통과할 수 있었다
- 감수한 것은 숨기지 않고 명시: 토큰 저장이 OS 키체인 → `localStorage`로 후퇴해 XSS에 노출된다. spec에 **"배포 전 재검토 필수"**로 못 박아 둠

📎 상세: [Notion — 3주차 5일차](https://cookie-moonstone-7ce.notion.site/3-5-2026-07-31-3aea44f2e1e381d79f07c1a8ff825571?source=copy_link)

### 6일차 · 2026-08-01

- 전날 정한 pre-flight 3가지(이슈/PR 단위 작업, 브라우저 확인은 사용자 몫, 화면 렌더 테스트 예외 2건)를 바탕으로 웹 전환 계획 SDD 실행 착수
- Task 1(ADR 0016~0019 작성, 0014 부분 대체) → Task 2(`web/` Vite+React+Tailwind 스캐폴딩) → Task 3(`api/` 레이어 이식) → Task 4(`AuthContext` localStorage 전환) → Task 5(공용 컴포넌트 5개) → Task 6(라우터·인증 가드·로그인 화면)까지 전부 이슈·PR 단위로 완료
- Task 7(그룹 목록 화면) 구현·2라운드 수정까지 진행했으나 사용자 브라우저 확인 대기로 머지는 다음 날로 이월
- jsdom `AbortSignal` vs undici `Request` 브랜드 체크 충돌, 리뷰어의 수정 제안이 오히려 새 결함을 만든 사례 등 트러블슈팅 6건. react-router v7 유지(v8 미업그레이드) 최종 결정

📎 상세: [Notion — 3주차 6일차](https://cookie-moonstone-7ce.notion.site/3-6-2026-08-01-3b0a44f2e1e38116a4d1eae78e423ec6?source=copy_link)

### 7일차 · 2026-08-02

- PR #18 머지로 Task 7 마무리 → 계획 외로 디자인 시스템 정비(브랜드/표면 토큰, `.card`/`.btn-*`)를 별도 이슈·PR로 삽입해 완료 → 그 여세로 Task 8~11(그룹 생성/합류, 멤버·초대 코드, 탭 간 세션 동기화, `app/` 완전 삭제(-14,460줄), 문서 갱신)을 전부 완주해 **웹 전환 계획(11개 태스크)을 하루 만에 마감**
- 이어서 초대 링크 전환(이슈 #30)과 관점별 호칭(이슈 #29)을 하나의 설계로 통합 — 브레인스토밍 중 기존 ADR 0007의 스키마(그룹당 호칭 하나)가 **그룹 안 상대성**(아버지는 나에게 "아빠", 어머니에게 "여보")을 못 담는다는 게 드러나 ADR 0021(관점별 호칭) 신설로 이어짐
- 설계+구현계획(PR #34) 작성 직후 같은 날 SDD로 Task 1~6 구현까지 완료(PR #36) — 서버 테스트 54/54, 웹 테스트 31/31 전건 통과, `typecheck`/`build` 정상

📎 상세: [Notion — 3주차 7일차](https://cookie-moonstone-7ce.notion.site/3-7-2026-08-02-3b0a44f2e1e381708fa9c7d5241f3120?source=copy_link)

## 다음 할 것

- 초대 링크·관점별 호칭 브라우저 수동 확인 5항목(링크 복사 → 로그인 후 자동 복귀 → 이름 확인 합류 → 상대 계정에 호칭 비공개 확인 → 재발급 후 이전 링크 410)
- 병합 완료된 `feat/emergency-vault-*` 브랜치 2개 정리
- 이슈 #28(카카오 로그인 OAuth) — 별도 설계 필요, 아직 미착수
- PIN 설정·검증, vault 토큰, 접근 감사 로그 — 여전히 미설계·미착수
