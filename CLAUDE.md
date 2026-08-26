# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 저장소 개요
Claude Code를 학습하는 6주 스터디 레포(2026.07.06~08.16)입니다. 별도의 빌드/린트/테스트 파이프라인은 없으며, 대부분의 작업은 Markdown 문서 작성·정리입니다. 1~2주차는 공식 문서 기반 기본기, 3~6주차는 참여자별 자유 주제 실전 프로젝트(언어 무관)를 진행합니다.

## 먼저 참고할 문서
- [README.md](README.md) — 스터디 개요·커리큘럼
- [CONTRIBUTING.md](CONTRIBUTING.md) — 폴더/브랜치/PR/커밋 규칙 (아래 요약)
- [members/README.md](members/README.md) — 개인 폴더 구조 템플릿

## 저장소 구조
```
weekNN/README.md      # 주차별 공통 목표·체크리스트 (멘토 작성, 임의 변경 금지)
members/<github-id>/  # 개인 학습 기록: week01.md~week06.md, project/(3주차~), retrospective.md(6주차)
resources/             # 참고 자료·링크 모음
```
개인 결과물은 항상 `members/<github-id>/` 아래에 두고, 그 폴더 구조는 자유롭게 확장 가능하되 다른 사람 폴더나 `weekNN/` 공통 자료는 건드리지 않습니다.

## Git / PR 워크플로우
- `main`에서 직접 작업하지 않고 브랜치를 파서 작업합니다. 브랜치명: `weekNN/<github-id>` (예: `week01/sxuhait`) 또는 `feat/<github-id>-project`.
- 커밋 메시지는 한글/영어 무관하게 무엇을 했는지 드러나야 합니다. `docs:`/`weekNN:`/Conventional Commits(`feat:`/`fix:`) 등을 상황에 맞게 사용합니다.
- PR 제목 예: `[week01] <github-id> 설치 & 첫 실습 정리`
- 막힌 부분은 GitHub Issue로 공유 (`question`/`blocker`/`share` 라벨 활용).

## 이 레포의 Claude Code 설정
- `.claude/commands/commit.md` — `/commit` 슬래시 커맨드: staged된 변경사항(`git diff --staged`)을 Conventional Commits 형식으로 커밋 메시지를 만들어 커밋.
- `.claude/settings.json` — PreToolUse 훅: `Edit`/`Write` 대상 파일 경로에 `.env`가 포함되면 차단(시크릿 보호). 저장소 루트의 `.env`는 `.gitignore`로 커밋 대상에서 제외되어 있습니다.

## 문서 작업 기준
- 가능한 한 작은 단위로 수정하고, 기존 구조·제목 계층을 유지하며 필요할 때만 자연스럽게 확장합니다.
- 한국어 작성이 기본이며, 사용자가 영어로 요청하면 영어로 처리합니다.
- 링크는 상대 경로로 작성해 기존 문서와 연결합니다.
- 불필요한 파일 생성을 피하고, 이미 존재하는 문서와 중복되지 않도록 합니다.
- 모호한 요청은 바로 가정하지 말고 필요한 경우 확인을 요청합니다.

## 🚀 빌드 및 실행 명령 (Build & Run)
- 이 저장소는 별도의 복잡한 빌드 파이프라인이 없습니다.
- 실습용 C++ 코드는 터미널에서 `g++ 파일명.cpp -o 파일명` 명령어로 컴파일한 뒤, `./파일명` (또는 Windows의 경우 `.\파일명.exe`) 명령어로 직접 실행하여 동작을 검증합니다.

## 🎨 코드 컨벤션 (Code Conventions)
- **주석 규칙**: 코드를 작성하거나 수정할 때, 모든 주석(Comment)은 반드시 '한국어 존댓말'로 상세하게 작성해야 합니다. (단순 영어 주석 금지)
- **커밋 메시지 규칙**: 커밋을 생성할 때 메시지 제목 맨 앞에 반드시 `[실습완료]` 라는 말머리를 포함하세요. (예: `[실습완료] 덧셈 기능 추가 및 테스트 완료`)

## 🚫 금지사항 (Prohibitions)
- `main` 브랜치에 직접 커밋하거나 푸시(Push)하는 것을 엄격히 금지합니다. 항상 별도의 브랜치에서 작업하세요.
- 멘토가 제공한 `weekNN/README.md` (주차별 공통 목표) 파일은 어떤 경우에도 임의로 수정하거나 삭제해선 안 됩니다.