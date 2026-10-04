# Yard Stick

A small web app that calculates a student's GPA on the 5.0 scale, built as a SIWESPRO Week 10 mini project. The name plays on the idea of a yardstick, a simple tool for measuring something, here used to measure academic performance.

## What it does

- Add any number of courses, each with a title, a letter grade, and a credit unit value
- Remove a course row you no longer need
- Calculate total credit units, total grade points, and GPA instantly
- Save a calculation to a history list, stored in the browser using localStorage
- View and clear saved calculation history on a separate page

## Pages

- `index.html` — Home page, introduces the app
- `calculator.html` — The GPA calculator form and result display
- `history.html` — Saved calculation history

## Technologies used

- HTML5 (semantic tags: header, main, nav, section, footer)
- CSS3 (CSS variables, Flexbox, a media query for mobile screens below 768px)
- Vanilla JavaScript (DOM manipulation, event listeners, localStorage)

## How to run

No server or build step is needed. Open `index.html` directly in any browser.

## Grading scale used

A = 5, B = 4, C = 3, D = 2, E = 1, F = 0, matching the standard 5.0 scale used by Nigerian universities.
