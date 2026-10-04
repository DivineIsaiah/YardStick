// This file is shared across pages. Each block checks whether its
// target elements exist on the current page before running, since
// calculator.html and history.html don't share the same elements.

// ---- Builds one new course row and returns it ----
function createCourseRow() {
    const row = document.createElement('div');
    row.className = 'course-row';
    row.innerHTML = `
        <input type="text" class="course-name" placeholder="Course title" required>
        <select class="course-grade" required>
            <option value="">Grade</option>
            <option value="5">A</option>
            <option value="4">B</option>
            <option value="3">C</option>
            <option value="2">D</option>
            <option value="1">E</option>
            <option value="0">F</option>
        </select>
        <input type="number" class="course-units" placeholder="Units" min="1" max="6" required>
        <button type="button" class="remove-row-btn">Remove</button>
    `;
    return row;
}

// ---- Removes a course row from the form, but keeps at least one row ----
function removeCourseRow(rowElement) {
    const container = document.getElementById('course-rows');
    if (container.children.length > 1) {
        rowElement.remove();
    } else {
        alert('At least one course row is required.');
    }
}

// ---- Reads all course rows and calculates total units, total points, and GPA ----
function calculateGPA() {
    const rows = document.querySelectorAll('.course-row');
    let totalUnits = 0;
    let totalPoints = 0;

    rows.forEach(row => {
        const grade = parseFloat(row.querySelector('.course-grade').value);
        const units = parseFloat(row.querySelector('.course-units').value);

        if (!isNaN(grade) && !isNaN(units) && units > 0) {
            totalUnits += units;
            totalPoints += grade * units;
        }
    });

    const gpa = totalUnits > 0 ? (totalPoints / totalUnits) : 0;

    return {
        totalUnits: totalUnits,
        totalPoints: totalPoints,
        gpa: gpa
    };
}

// ---- Saves a GPA result to localStorage, keeping the most recent 20 entries ----
function saveResultToHistory(result) {
    const existing = JSON.parse(localStorage.getItem('gpaHistory')) || [];
    existing.unshift({
        date: new Date().toLocaleString(),
        totalUnits: result.totalUnits,
        totalPoints: result.totalPoints,
        gpa: result.gpa.toFixed(2)
    });
    const trimmed = existing.slice(0, 20);
    localStorage.setItem('gpaHistory', JSON.stringify(trimmed));
}

// ---- Renders the saved history list on history.html ----
function renderHistory() {
    const listContainer = document.getElementById('history-list');
    const emptyMessage = document.getElementById('empty-message');
    if (!listContainer) return;

    const history = JSON.parse(localStorage.getItem('gpaHistory')) || [];

    if (history.length === 0) {
        emptyMessage.classList.remove('hidden');
        listContainer.innerHTML = '';
        return;
    }

    emptyMessage.classList.add('hidden');
    listContainer.innerHTML = history.map(entry => `
        <div class="history-entry">
            <p class="entry-date">${entry.date}</p>
            <p>Units: ${entry.totalUnits} | Points: ${entry.totalPoints} | <strong>GPA: ${entry.gpa}</strong></p>
        </div>
    `).join('');
}

// ---- Calculator page logic ----
const gpaForm = document.getElementById('gpa-form');
if (gpaForm) {
    const courseRows = document.getElementById('course-rows');
    const addRowBtn = document.getElementById('add-row-btn');
    const clearBtn = document.getElementById('clear-btn');
    const saveBtn = document.getElementById('save-btn');
    const resultBox = document.getElementById('result-box');
    let latestResult = null;

    // Add a new course row when the button is clicked
    addRowBtn.addEventListener('click', () => {
        courseRows.appendChild(createCourseRow());
    });

    // Remove a course row, using event delegation since rows are added dynamically
    courseRows.addEventListener('click', (e) => {
        if (e.target.classList.contains('remove-row-btn')) {
            removeCourseRow(e.target.closest('.course-row'));
        }
    });

    // Calculate GPA on form submit, prevents the default page reload
    gpaForm.addEventListener('submit', (e) => {
        e.preventDefault();
        latestResult = calculateGPA();

        document.getElementById('total-units').textContent = latestResult.totalUnits;
        document.getElementById('total-points').textContent = latestResult.totalPoints;
        document.getElementById('gpa-result').textContent = latestResult.gpa.toFixed(2);

        resultBox.classList.remove('hidden');
    });

    // Reset the form back to a single empty row
    clearBtn.addEventListener('click', () => {
        courseRows.innerHTML = '';
        courseRows.appendChild(createCourseRow());
        resultBox.classList.add('hidden');
        latestResult = null;
    });

    // Save the most recent calculation to localStorage
    saveBtn.addEventListener('click', () => {
        if (latestResult) {
            saveResultToHistory(latestResult);
            alert('Result saved! Check the History page to view it.');
        }
    });
}

// ---- History page logic ----
const clearHistoryBtn = document.getElementById('clear-history-btn');
if (clearHistoryBtn) {
    renderHistory();

    clearHistoryBtn.addEventListener('click', () => {
        localStorage.removeItem('gpaHistory');
        renderHistory();
    });
}
