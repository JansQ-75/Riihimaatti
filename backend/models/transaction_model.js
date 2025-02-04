const db = require('../database');

// Get all transactions from all accounts
const transaction = {
  getAll: function (callback) {
    return db.query('SELECT * FROM transaction;', callback);
  },

// Get transactions by account id
  transactionsById: function (idbank_account, callback) {
    return db.query(
      ` SELECT t.transaction_date, t.withdrawal, b.bank_account_number, c.cardnumber 
      FROM transaction t
      JOIN bank_account b ON t.idbank_account=b.idbank_account 
      LEFT JOIN card c ON t.idcard=c.idcard 
      WHERE b.idbank_account=?`,
      [idbank_account], callback
    );
  },

// Show transactions, previous ten, next ten
showTransactions: function (idbank_account, offsetValue, callback) {
  return db.query('CALL showTransactions (?, ?)',
    [idbank_account, offsetValue],
    callback);
},

// Do a withdrawal 
makeWithdrawal: function (account_type, idbank_account, idcard, withdrawal, callback) {
  if (account_type === "debit") {
    return db.query(
      'CALL makeDebitWithdrawal (?, ?, ?)',
      [idbank_account, idcard, withdrawal],
      callback
    );
  } else if (account_type === "credit") {
    return db.query(
      'CALL makeCreditWithdrawal (?, ?, ?)',
      [idbank_account, idcard, withdrawal],
      callback
    );
  }
},

// Delete
delete: function (idtransaction, callback) {
  return db.query(
    'DELETE FROM transaction WHERE idtransaction=?',
    [idtransaction],
    callback,
  );
},

// Update
update: function (idtransaction, transaction_data, callback) {
    db.query('SELECT * FROM transaction WHERE idtransaction=?', [idtransaction], (err, result) => {
      if (err) {
        return callback(err);
      }
      if (!result.length) {
        return callback({ error: 'Transaction not found' });
      }
      const previous = result[0];

      // Updates only fields where new info is given
      return db.query(
        'UPDATE transaction SET transaction_date=?, withdrawal=?, idbank_account=?, idcard=? WHERE idtransaction=?',
        [
          transaction_data.transaction_date || previous.transaction_date,
          transaction_data.withdrawal || previous.withdrawal,
          transaction_data.idbank_account || previous.idbank_account,
          transaction_data.idcard || previous.idcard,
          idtransaction
        ],
        function (err, result) {
          if (err) {
            return callback(err);
          }
          callback(null, result);
        },
      );
    });
},


};
module.exports = transaction;
