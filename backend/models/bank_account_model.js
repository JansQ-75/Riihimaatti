const db = require('../database');

const bank_account = {
    //Get all bank account data
    getAll: function (callback) {
        return db.query('SELECT * FROM bank_account;', callback);
    },

    // Get all bank account data by id
    getById: function (idbank_account, callback) {
        return db.query('SELECT * FROM bank_account WHERE idbank_account=?', [idbank_account], callback);
    },

    // Get all bank account data by accountnumber
    getByAccountNbr: function (bank_account_number, callback) {
        return db.query('SELECT * FROM bank_account WHERE bank_account_number=?', [bank_account_number], callback);
    },

    // Add a bank account
    add: function (bank_account_data, callback) {
        return db.query('INSERT INTO bank_account(bank_account_number, account_type, balance, credit_limit, idcustomer) values (?,?,?,?,?)', [bank_account_data.bank_account_number, bank_account_data.account_type, bank_account_data.balance, bank_account_data.credit_limit, bank_account_data.idcustomer], callback);
    },

    // Update a bank account
    // TÄÄ EI VARMAAN OO HYVÄ???
    update: function (idbank_account, bank_account_data, callback) {
        return db.query('UPDATE bank_account SET bank_account_number=?, account_type=?, balance=?, credit_limit=?, idcustomer=? WHERE idbank_account=?', [bank_account_data.bank_account_number, bank_account_data.account_type, bank_account_data.balance, bank_account_data.credit_limit, bank_account_data.idcustomer, idbank_account], callback);
    },

    // Update bank account info. vaihtaa muut paitsi tilinron.
    update2: function (bank_account_number, bank_account_data, callback) {
        return db.query('UPDATE bank_account SET account_type=?, balance=?, credit_limit=?, idcustomer=? WHERE bank_account_number=?', [bank_account_data.account_type, bank_account_data.balance, bank_account_data.credit_limit, bank_account_data.idcustomer, bank_account_number], callback);
    }
}

module.exports = bank_account;