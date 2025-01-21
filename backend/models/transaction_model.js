const db = require('../database');

const transaction = {
  getAll: function (callback) {
    return db.query('SELECT * FROM transaction;', callback);
  },
  // Todo

// Get transaction date
getTransaction_date: function (transaction_date, callback){
  return db.query('SELECT * FROM transaction WHERE transaction_date=?', [transaction_date], callback);
},

// Withdraw money, 20, 40, 50, 100
withdrawal: function (idbank_account, amountToWithdraw, callback) {
  return db.query('UPDATE bank_account SET balance = balance - ? WHERE idbank_account=? AND balance >= ?',
     [amountToWithdraw, idbank_account, amountToWithdraw], callback);
},

// Show previous 10 transactions
showPreviousTransactions: function (transaction, callback){
  return db.query('SELECT * FROM transaction ORDER BY transaction_date DESC LIMIT 10',
     [transaction], callback)
},

// Show next 10 transactions
showNextTransactions: function (transaction, callback){
  return db.query('SELECT * FROM transaction ORDER BY transaction_date ASC LIMIT 10', 
    [transaction], callback)
},


//Do a debit withdrawal
makeDebitWithdrawal: function (transaction_data, callback) {
    return db.query(
      'CALL makeDebitWithdrawal (?, ?, ?)',
      [
        transaction_data.idbank_account,
        transaction_data.idcard,
        transaction_data.withdrawal,
      ],
      callback,
    );
},

//Do a credit withdrawal
makeCreditWithdrawal: function (transaction_data, callback) {
  return db.query(
    'CALL makeCreditWithdrawal (?, ?, ?)',
    [
      transaction_data.idbank_account,
      transaction_data.idcard,
      transaction_data.withdrawal,
    ],
    callback,
  );
},

//Get all
atm_transactions: function (transaction_data, callback) {
  return db.query(
    'CALL atm_transactions (?)',
    [
      transaction_data.idbank_account
    ],
    callback,
  );
}

};

module.exports = transaction;
