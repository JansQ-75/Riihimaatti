const db = require('../database');

const bank_account = {
    //Get all bank account data
    getAll: function (callback) {
        return db.query
            (
                'SELECT * FROM bank_account;', callback
            );
    },

    // Get all bank account data by id
    getById: function (idbank_account, callback) {
        return db.query
            (
                'SELECT * FROM bank_account WHERE idbank_account=?',
                [
                    idbank_account
                ],
                callback
            );
    },

    // Get all bank account data by accountnumber
    getByAccountNbr: function (bank_account_number, callback) {
        return db.query
            (
                'SELECT * FROM bank_account WHERE bank_account_number=?',
                [
                    bank_account_number
                ],
                callback
            );
    },

    // Add bank account
    add: function (bank_account_data, callback) {
        return db.query
            (
                'INSERT INTO bank_account(bank_account_number, account_type, balance, credit_limit, idcustomer) values (?,?,?,?,?)',
                [
                    bank_account_data.bank_account_number,
                    bank_account_data.account_type,
                    bank_account_data.balance,
                    bank_account_data.credit_limit,
                    bank_account_data.idcustomer
                ],
                callback
            );
    },

    // Update bank account. Replace entire data
    update: function (idbank_account, bank_account_data, callback) {
        return db.query
            (
                'UPDATE bank_account SET bank_account_number=?, account_type=?, balance=?, credit_limit=?, idcustomer=? WHERE idbank_account=?',
                [
                    bank_account_data.bank_account_number,
                    bank_account_data.account_type,
                    bank_account_data.balance,
                    bank_account_data.credit_limit,
                    bank_account_data.idcustomer,
                    idbank_account
                ],
                callback
            );
    },

    // Change balance
    updateBalance: function (idbank_account, bank_account_data, callback) {
        return db.query
            (
                'UPDATE bank_account SET balance=? WHERE idbank_account=?',
                [
                    bank_account_data.balance,
                    idbank_account
                ],
                callback
            );
    },

    // Change credit_limit
    updateCredit: function (idbank_account, bank_account_data, callback) {
        return db.query
            (
                'UPDATE bank_account SET credit_limit=? WHERE idbank_account=?',
                [
                    bank_account_data.credit_limit,
                    idbank_account
                ],
                callback
            );
    },

    //Delete bank account
    delete: function (idbank_account, callback) {
        return db.query
            (
                'DELETE FROM bank_account WHERE idbank_account=?',
                [
                    idbank_account
                ],
                callback
            );
    },
}

module.exports = bank_account;