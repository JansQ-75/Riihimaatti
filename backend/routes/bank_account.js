const express = require('express');
const router = express.Router();
const bank_account = require('../models/bank_account_model');
const { response } = require('../app');

router.get('/', function (request, response) {
    bank_account.getAll(function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result);
        }
    })
});

router.get('/by-id/:idbank_account', function (request, response) {
    bank_account.getById(request.params.idbank_account, function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result[0]);
        }
    })
});

router.get('/by-account-nbr/:bank_account_number', function (request, response) {
    bank_account.getByAccountNbr(request.params.bank_account_number, function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result[0]);
        }
    })
});

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

router.put('/by-account-nbr/:bank_account_number', function (request, response) {
    bank_account.update2(request.params.bank_account_number, request.body, function (err, result) {
        if (err) {
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

module.exports = router;