const express = require('express');
const router = express.Router();
const customer = require('../models/customer_model');
const { checkAdmin } = require('../authentication');

/**
 * Get all Customers data - Admin Access only
 */
router.get('/', checkAdmin, function (request, response) {
  customer.getAll(function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result);
    }
  });
});

/**
 * Get Customer data. Admin & Customer access
 */
router.get(
  '/:idcustomer',
  customer.validateCustomerAccess,
  function (request, response) {
    customer.getById(request.params.idcustomer, function (err, result) {
      if (err) {
        response.json(err);
      } else {
        response.json(result[0]);
      }
    });
  },
);

/**
 * Add Customer. Admin access only
 */
router.post('/', checkAdmin, function (request, response) {
  customer.add(request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

/**
 * Update Customer data - Admin access only
 */
router.put(
  '/:idcustomer',
  customer.validateCustomerAccess,
  function (request, response) {
    customer.update(
      request.params.idcustomer,
      request.body,
      function (err, result) {
        if (err) {
          response.json(err);
        } else {
          response.json(result.affectedRows);
        }
      },
    );
  },
);

/**
 * Delete user - Admin access only
 */
router.delete('/:idcustomer', checkAdmin, function (request, response) {
  customer.delete(request.params.idcustomer, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

module.exports = router;
