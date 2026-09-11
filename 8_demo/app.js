const accounts = new Map();
const accountType = document.getElementById("accountType");
const rateField = document.getElementById("rateField");
const overdraftField = document.getElementById("overdraftField");
const accountForm = document.getElementById("accountForm");
const activeAccount = document.getElementById("activeAccount");
const targetAccount = document.getElementById("targetAccount");
const accountsTable = document.getElementById("accountsTable");
const message = document.getElementById("message");
const amountInput = document.getElementById("amount");

function money(value) {
    return Number(value).toFixed(2);
}

function getSelectedAccount() {
    return accounts.get(activeAccount.value);
}

function addHistory(account, text) {
    account.history.push(text);
}

function render() {
    const previousActive = activeAccount.value;
    const previousTarget = targetAccount.value;
    const options = Array.from(accounts.values())
        .map((account) => `<option value="${account.number}">${account.number} - ${account.name}</option>`)
        .join("");

    activeAccount.innerHTML = options || "<option value=''>No accounts</option>";
    targetAccount.innerHTML = options || "<option value=''>No accounts</option>";

    if (accounts.has(previousActive)) {
        activeAccount.value = previousActive;
    }

    if (accounts.has(previousTarget)) {
        targetAccount.value = previousTarget;
    }

    accountsTable.innerHTML = Array.from(accounts.values())
        .map((account) => {
            const extra = account.type === "Savings"
                ? `Interest: ${account.interestRate}%`
                : `Overdraft: $${money(account.overdraftLimit)}`;

            return `
                <tr>
                    <td>#${account.number}</td>
                    <td>${account.name}</td>
                    <td><span class="account-badge ${account.type.toLowerCase()}">${account.type}</span></td>
                    <td>$${money(account.balance)}</td>
                    <td><span class="extra-info">${extra}</span></td>
                </tr>
            `;
        })
        .join("");
}

function setMessage(text) {
    message.textContent = text;
}

accountType.addEventListener("change", () => {
    const isSavings = accountType.value === "savings";
    rateField.classList.toggle("hidden", !isSavings);
    overdraftField.classList.toggle("hidden", isSavings);
});

accountForm.addEventListener("submit", (event) => {
    event.preventDefault();

    const number = document.getElementById("accountNumber").value.trim();
    const name = document.getElementById("accountName").value.trim();
    const balance = Number(document.getElementById("openingBalance").value);

    if (accounts.has(number)) {
        setMessage("Account number already exists.");
        return;
    }

    const isSavings = accountType.value === "savings";
    const account = {
        number,
        name,
        balance,
        type: isSavings ? "Savings" : "Current",
        interestRate: Number(document.getElementById("interestRate").value),
        overdraftLimit: Number(document.getElementById("overdraftLimit").value),
        history: [`Account created with balance ${money(balance)}`],
    };

    accounts.set(number, account);
    accountForm.reset();
    accountType.dispatchEvent(new Event("change"));
    render();
    activeAccount.value = number;
    setMessage(`${account.type} account created successfully.\nAccount Number: ${number}\nName: ${name}`);
});

document.querySelector(".button-grid").addEventListener("click", (event) => {
    const button = event.target.closest("button");
    if (!button) {
        return;
    }

    const account = getSelectedAccount();
    if (!account) {
        setMessage("Please create an account first.");
        return;
    }

    const action = button.dataset.action;
    const amount = Number(amountInput.value);

    if (["deposit", "withdraw", "transfer"].includes(action) && amount <= 0) {
        setMessage("Enter a valid amount.");
        return;
    }

    if (action === "deposit") {
        account.balance += amount;
        addHistory(account, `Deposited ${money(amount)}`);
        setMessage(`Deposited ${money(amount)} successfully.\nNew Balance: ${money(account.balance)}`);
    }

    if (action === "withdraw") {
        const allowedBalance = account.type === "Current"
            ? account.balance + account.overdraftLimit
            : account.balance;

        if (amount > allowedBalance) {
            setMessage("Withdrawal failed. Insufficient balance or overdraft limit.");
            return;
        }

        account.balance -= amount;
        addHistory(account, `Withdrawn ${money(amount)}`);
        setMessage(`Withdrawn ${money(amount)} successfully.\nNew Balance: ${money(account.balance)}`);
    }

    if (action === "transfer") {
        const target = accounts.get(targetAccount.value);

        if (!target || target.number === account.number) {
            setMessage("Choose a different target account for transfer.");
            return;
        }

        const allowedBalance = account.type === "Current"
            ? account.balance + account.overdraftLimit
            : account.balance;

        if (amount > allowedBalance) {
            setMessage("Transfer failed. Insufficient balance or overdraft limit.");
            return;
        }

        account.balance -= amount;
        target.balance += amount;
        addHistory(account, `Transferred ${money(amount)} to account ${target.number}`);
        addHistory(target, `Received ${money(amount)} from account ${account.number}`);
        setMessage(`Transferred ${money(amount)} to ${target.name}.\nNew Balance: ${money(account.balance)}`);
    }

    if (action === "interest") {
        if (account.type !== "Savings") {
            setMessage("Interest can be added only to Savings Accounts.");
            return;
        }

        const interest = account.balance * account.interestRate / 100;
        account.balance += interest;
        addHistory(account, `Interest added ${money(interest)}`);
        setMessage(`Interest added: ${money(interest)}\nNew Balance: ${money(account.balance)}`);
    }

    if (action === "details") {
        const extra = account.type === "Savings"
            ? `Interest Rate: ${account.interestRate}%`
            : `Overdraft Limit: ${money(account.overdraftLimit)}`;

        setMessage(`Account Details\nNumber: ${account.number}\nName: ${account.name}\nType: ${account.type}\nBalance: ${money(account.balance)}\n${extra}`);
    }

    if (action === "history") {
        setMessage(account.history.length ? account.history.join("\n") : "No transactions yet.");
    }

    render();
});

render();
