# Week 03 — 새싹일기 프로젝트 착수

## 무엇을 / 왜 만드는가
지역아동센터 대학생 멘토를 위한 멘토링 코파일럿 웹앱.
누적된 일지·출석 데이터를 AI가 분석해 아동별 학습 취약점과
다음 지도 포인트를 먼저 제안하는 것이 최종 목표.

## 기술 스택
Next.js (App Router) + TypeScript + Tailwind + Supabase (Postgres/Auth)

## 이번 주 진행 (3주차)
- 프로젝트 셋업, CLAUDE.md 작성
- DB 스키마 설계: mentors / mentees / weekday_registrations /
  attendance / session_logs (+ RLS 적용, 멘토별 데이터 격리)
- 로그인(Supabase Auth) → 멘티 목록 → 일지 작성/이력
- 멘티별 월간 달력, 출석 체크(출석/결석/지각/사유결석 + 사유 입력)
- 센터 공용 행사 달력, 센터 수업(요일별) 관리 + 수강 등록

## 프로젝트 레포
https://github.com/sxuhait/saessak_diary

## 다음 주 계획 (4주차)
- AI 취약점 진단·제안 엔진 프로토타입
