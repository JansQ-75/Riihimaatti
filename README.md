# ATM - Riihimaatti 
#### *Group 17 (TVT24KMO)*

---

## Table of contents

*sisällysluettelo tähän*
- *Project introduction*
- *Project goals*
- *Usage instructions*
- *Documentation*
- *Project outcome*
- *Contributors*

---

## Project goals

 :star: Our goal was to create an ATM application which combines SQL database, REST API, Linux server and Qt Creator.
 :star: Our goal was to become confident users of technologies, which we used in the project.
 :star: Our aim was to use the knowledge, which we learnt in previous courses at the Oulu University of Applied Sciences, and apply our knowledge. Moreover, to expand our knowledge in given fields and technologies. 

---

## Usage instructions

*Jotain fiksua tähän* 

---

## Documentation

### Backend

```sh
cd backend
npm install
npm run dev
```
#### API??

#### Server/Linux??

#### Database

For this project we created SQL database with MySQLWorkbench

**ER-diagram:**

<img src="ERdiagram.png">

**Design for our database:**
- Customer
    - Columns: firstname, lastname, address, phonenumber
    - Customer can have many accounts
    - Customer can have multiple cards
- Card
    - Columns: cardnumber, pin-number, card type, locked status and foreign key for customer
    - Card can have multiple access right to different accounts (debit, credit, debit/credit)
    - Card must have one owner
    - Card can have multiple transactions
- Bank account
    - Columns: account number, account type, balance, credit limit and foreign key for customer
    - Bank account must have only one owner
    - Bank account can have multiple transactions
    - Bank account can grant multiple access rights to cards
- Transaction
    - Columns: transaction date, withdrawal amount, foreign keys for bank account and card
    - One transaction can have one card
    - One transaction must have one bank account
- Access rights
    - Columns: foreign keys for card and bank account
    - One access right must have one card and one bank account

### Frontend

#### User interface (QT)

First, the app opens a login interface. The ATM app asks customer's card number and pin code. After succeccfull authentification, it opens the main interface of the ATM app. There are four buttons in the ATM app's main interface. 
- The "Show balance" button shows the balance of the logged in customer's bank account. 
- The "Make a withdrawal" button opens a new interface where customer can choose the desired amount for withdrawal.
- The "Browse transactions" button lists 10 transactions to a new interface where customer can browse previous transactions.
- The button for logout.

---

## Project outcome

---

## Contributors