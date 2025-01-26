const express = require('express');
const router = express.Router();
const bank_account = require('../models/bank_account_model');
const { checkAdmin } = require('../authentication');

// Route handler for GET request to get info of all bank accounts
// Only for Admin
router.get('/', checkAdmin, function (request, response) {
    bank_account.getAll(function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result);
        }
    })
});

// Route handler for GET request to get info of a specific bank account (via accountId)
// Admin or validated user
router.get(
    '/by-id/:idbank_account',
    bank_account.validateAccountIdAccess,
    function (request, response) {
        bank_account.getById(request.params.idbank_account, function (err, result) {
            if (err) {
                response.json(err);
            }
            else {
                response.json(result[0]);
            }
        })
    });

// Route handler for GET request to get info of a specific bank account (via accountnumber)
// Admin or validated user
router.get(
    '/by-account-nbr/:bank_account_number',
    bank_account.validateAccountNumberAccess,
    function (request, response) {
        bank_account.getByAccountNbr(request.params.bank_account_number, function (err, result) {
            if (err) {
                response.json(err);
            }
            else {
                response.json(result[0]);
            }
        })
    });

// Route handler for POST request to add bank account to database
router.post('/', function (request, response) {
    bank_account.add(request.body, function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

// Route handler for PUT request to update account info
router.put('/by-id/:idbank_account', function (request, response) {
    bank_account.update(request.params.idbank_account, request.body, function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

// Route handler for PATCH request to update only balance of a bank account
router.patch('/by-id/balance/:idbank_account', function (request, response) {
    bank_account.updateBalance(request.params.idbank_account, request.body, function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

// Route handler for PATCH request to update only credit of a bank account
router.patch('/by-id/credit/:idbank_account', function (request, response) {
    bank_account.updateCredit(request.params.idbank_account, request.body, function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

// Route handler for DELETE request to delete account from database
router.delete('/:idbank_account', function (request, response) {
    bank_account.delete(request.params.idbank_account, function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

module.exports = router;