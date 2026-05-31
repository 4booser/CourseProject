#include "services/discipline_service.h"

#include "repositories/discipline_repository.h"
#include "repositories/workload_repository.h"

namespace services
{
    OperationResult ValidateDiscipline(const models::Discipline& discipline)
    {
        if (discipline.name.empty())
        {
            return OperationResult::Fail("Назва дисциплiни не може бути порожньою.");
        }

        if (discipline.quota == 0)
        {
            return OperationResult::Fail("Кiлькiсть годин дисциплiни повинна бути бiльше 0.");
        }

        return OperationResult::Ok();
    }

    OperationResult CanDeleteDiscipline(unsigned short discipline_id)
    {
        if (!GetDisciplineById(discipline_id).has_value())
        {
            return OperationResult::Fail("Дисциплiну з таким Id не знайдено.");
        }

        if (HasWorkloadForDiscipline(discipline_id))
        {
            return OperationResult::Fail("Операцiю заблоковано: дисциплiна використовується в навантаженнi.");
        }

        return OperationResult::Ok();
    }
}
