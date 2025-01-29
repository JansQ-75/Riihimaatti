const db = require('../database');

const bank_account = {
    //Get all bank account data
    getAll: function (callback) {
        return db.query
            (
                'SELECT * FROM bank_account;', callback
            );
    },

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

    // Update bank account. Replace or modify entire data
    update: function (idbank_account, bank_account_data, callback) {
        // Query to get wanted account data
        db.query('SELECT * FROM bank_account WHERE idbank_account=?', [idbank_account], (err, result) => {
            if (err) {
                return callback(err);
            }
            if (!result.length) {
                return callback({ error: 'Account not found' });
            }
            // Sets current account data values to "previous values"
            const previous = result[0];

            // Query to update account data
            // if new value isn't set, then previous value remains
            return db.query
                (
                    'UPDATE bank_account SET bank_account_number=?, account_type=?, balance=?, credit_limit=?, idcustomer=? WHERE idbank_account=?',
                    [
                        bank_account_data.bank_account_number || previous.bank_account_number,
                        bank_account_data.account_type || previous.account_type,
                        bank_account_data.balance || previous.balance,
                        bank_account_data.credit_limit || previous.credit_limit,
                        bank_account_data.idcustomer || previous.idcustomer,
                        idbank_account
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

    checkCardAccess: function (cardnumber, callback) {
        return db.query
            ('SELECT b.idbank_account, b.account_type FROM bank_account b JOIN access_rights a ON b.idbank_account=a.idbank_account JOIN card c ON a.idcard=c.idcard WHERE c.cardnumber=?',
                [
                    cardnumber
                ],
                callback
            );

    },

    // validate bank account id
    validateAccountIdAccess: function (req, res, next) {
        if (req.isAdmin) {
            return next();
        }
        const query = `
            SELECT b.idbank_account
            FROM bank_account b 
            JOIN access_rights a ON b.idbank_account=a.idbank_account 
            JOIN card c ON a.idcard=c.idcard 
            WHERE b.idbank_account=? AND c.cardnumber=?;
          `;

        db.query(query, [req.params.idbank_account, req.cardnumber], (err, result) => {
            if (err)
                return res
                    .status(500)
                    .json({ error: `Internal Server Error. Sit tight!` });

            if (!result.length)
                return res.status(403).json({ error: `Access denied. Forbidden Kingdom. You shall not pass!` });

            next();
        });
    },

    // validate bank account accountnumber
    validateAccountNumberAccess: function (req, res, next) {
        if (req.isAdmin) {
            return next();
        }
        const query = `
           SELECT b.bank_account_number
            FROM bank_account b 
            JOIN access_rights a ON b.idbank_account=a.idbank_account 
            JOIN card c ON a.idcard=c.idcard 
            WHERE b.bank_account_number=? AND c.cardnumber=?;
          `;

        db.query(query, [req.params.bank_account_number, req.cardnumber], (err, result) => {
            if (err)
                return res
                    .status(500)
                    .json({ error: `Internal Server Error. Sit tight!` });

            if (!result.length)
                return res.status(403).json({ error: `Access denied. Forbidden Kingdom. You shall not pass!` });

            next();
        });
    },

    // validate card access to an account
    validateCardAccess: function (req, res, next) {
        if (req.isAdmin) {
            return next();
        }
        const query = `
            SELECT b.idbank_account
            FROM bank_account b 
            JOIN access_rights a ON b.idbank_account=a.idbank_account 
            JOIN card c ON a.idcard=c.idcard 
            WHERE c.cardnumber=?;
          `;

        db.query(query, [req.params.cardnumber], (err, result) => {
            if (err)
                return res
                    .status(500)
                    .json({ error: `Internal Server Error. Sit tight!` });


            if (req.cardnumber != req.params.cardnumber)
                return res.status(403).json({ error: 'Access denied. Forbidden Kingdom. You shall not pass!' });

            else
                next();
        });
    },
}

module.exports = bank_account;